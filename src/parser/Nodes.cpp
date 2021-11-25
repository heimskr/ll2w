#include <iostream>
#include <sstream>

#include "compiler/Variable.h"
#include "parser/Lexer.h"
#include "parser/Nodes.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "parser/Util.h"
#include "util/Deleter.h"
#include "util/Util.h"

namespace LL2W {

// MetadataDef

	MetadataDef::MetadataDef(ASTNode *dotident_node, ASTNode *distinct_node, ASTNode *list):
		BaseNode(llvmParser, LLVM_METADATA, StringSet::intern(dotident_node->concatenate().c_str())) {
		locate(dotident_node);
		distinct = distinct_node != nullptr;
		if (distinct_node)
			delete distinct_node;
		adopt(dotident_node);
		adopt(list);
	}

	std::string MetadataDef::debugExtra() const {
		return " \e[36m" + std::string(distinct? "" : "not ") + "distinct\e[0m";
	}

// HeaderNode

	HeaderNode::HeaderNode(bool simple, ASTNode *node): BaseNode(llvmParser, LLVM_BLOCKHEADER, "") {
		Deleter deleter(node);
		locate(node);
		ASTNode *list;

		if (simple) {
			label = StringSet::intern(node->lexerInfo->substr(0, node->lexerInfo->size() - 1));
			list = node->at(1);
		} else {
			label = node->at(0)->lexerInfo;
			list = node->at(2);
		}

		preds.reserve(list->size());
		for (const ASTNode *pred: *list)
			preds.push_back(StringSet::intern(pred->lexerInfo->substr(1)));
	}

	HeaderNode::HeaderNode(ASTNode *node): BaseNode(llvmParser, LLVM_BLOCKHEADER, "") {
		Deleter deleter(node);
		locate(node);
		label = StringSet::intern(node->lexerInfo->substr(0, node->lexerInfo->size() - 1));
	}

	std::string HeaderNode::debugExtra() const {
		std::stringstream out;
		out << "\e[2;4m<label>:" << label << "; preds =";
		for (const std::string *pred: preds)
			out << " %" << *pred;
		out << "\e[0m";
		return out.str();
	}

// AttributesNode

	AttributesNode::AttributesNode(ASTNode *node): BaseNode(llvmParser, LLVMTOK_ATTRIBUTES, "") {
		Deleter deleter(node);
		index = node->at(0)->atoi();
		for (ASTNode *child: *node->at(1)) {
			switch (child->symbol) {
				case LLVMTOK_FNATTR_BASIC:
					for (const std::pair<const FnAttr, std::string> &pair: fnattr_map)
						if (*child->lexerInfo == pair.second) {
							functionAttributes.insert(pair.first);
							break;
						}
					break;
				case LLVMTOK_PARATTR:
					for (const std::pair<const ParAttr, std::string> &pair: parattr_map)
						if (*child->lexerInfo == pair.second) {
							parameterAttributes.insert(pair.first);
							break;
						}
					break;
				case LLVMTOK_STRING:
					stringAttributes.insert({child->extracted(), StringSet::intern("")});
					break;
				case LLVMTOK_EQUALS:
					stringAttributes.insert({child->at(0)->extracted(), child->at(1)->extracted()});
					break;
				case LLVMTOK_ALLOCSIZE:
					allocsizeSize = child->at(0)->atoi();
					if (1 < child->size())
						allocsizeCount = child->at(1)->atoi();
					break;
				// Why oh why do these have to be ambiguous?
				case LLVMTOK_WRITEONLY:
					parameterAttributes.insert(ParAttr::Writeonly);
					functionAttributes.insert(FnAttr::writeonly);
					break;
				case LLVMTOK_READNONE:
					parameterAttributes.insert(ParAttr::Readnone);
					functionAttributes.insert(FnAttr::readnone);
					break;
				case LLVMTOK_READONLY:
					parameterAttributes.insert(ParAttr::Readonly);
					functionAttributes.insert(FnAttr::readonly);
					break;
				default:
					node->at(1)->debug();
					throw std::runtime_error("Invalid child of ATTRIBUTE_LIST: " + std::string(child->getName()));
			}
		}
	}

	std::string AttributesNode::debugExtra() const {
		std::stringstream out;
		out << "attributes #\e[92m" << index << "\e[0m \e[2m= { \e[0m";
		for (FnAttr attr: functionAttributes)
			out << "\e[34m" << fnattr_map.at(attr) << "\e[0m ";
		for (const std::pair<const std::string * const, const std::string *> &pair: stringAttributes) {
			out << "\e[93m\"" << *pair.first << "\"\e[0m";
			if (!pair.second->empty())
				out << "\e[2m=\e[0;93m\"" << *pair.second << "\"\e[0m";
			out << " ";
		}
		out << "\e[2m}\e[0m";
		return out.str();
	}

// InstructionNode

	InstructionNode::InstructionNode(const std::string *str): BaseNode(llvmParser, LLVM_INSTRUCTION, str) {}
	InstructionNode::InstructionNode(): BaseNode(llvmParser, LLVM_INSTRUCTION, "") {}

	void InstructionNode::handleUnibangs(ASTNode *unibangs) {
		for (const ASTNode *sub: *unibangs) {
			if (sub->symbol == LLVMTOK_PROF)
				prof = sub->front()->atoi();
			else if (sub->symbol == LLVMTOK_CALLEES)
				callees = sub->front()->atoi();
			else if (sub->symbol == LLVMTOK_DBG)
				debugIndex = sub->front()->atoi();
		}
	}

// Reader

	std::vector<std::shared_ptr<LocalValue>> Reader::allLocals() {
		std::vector<ValuePtr> values = allValues();
		std::vector<std::shared_ptr<LocalValue>> out;
		out.reserve(values.size());
		for (ValuePtr value: values) {
			if (value && value->isLocal())
				out.push_back(std::dynamic_pointer_cast<LocalValue>(value));
		}
		return out;
	}

	void Reader::replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) {
		for (std::shared_ptr<LocalValue> value: allLocals()) {
			if (value->variable->id == to_replace->id)
				value->variable = new_var;
		}
	}

// Writer

	std::string Writer::getResult() const {
		return "\e[32m" + (variable? std::string(*variable) : "%" + *result) + "\e[0m";
	}

	void Writer::replaceWritten(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) {
		if (!variable || variable->id != to_replace->id)
			return;
		variable = new_var;
	}

// SelectNode

	SelectNode::SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type, ASTNode *condition_value,
	                       ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, condition_type, condition_value, type1, val1, type2, val2);
		handleUnibangs(unibangs);
		result = result_->extracted();
		getFastmath(fastmath, fastmath_);
		conditionType = getType(condition_type);
		conditionValue = getValue(condition_value);
		firstType = getType(type1);
		firstValue = getValue(val1);
		secondType = getType(type2);
		secondValue = getValue(val2);
	}

	std::string SelectNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m" << getResult() << " \e[2m= \e[0;91mselect\e[0;38;5;202m" << fastmath << " " << *conditionType
		    << " " << *conditionValue << "\e[2m,\e[0m " << *firstType << " " << *firstValue << "\e[2m,\e[0m "
		    << *secondType << " " << *secondValue;
		return out.str();
	}

// AllocaNode

	AllocaNode::AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
	                       ASTNode *addrspace_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, inalloca_, type_, numelements_, align_, addrspace_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		inalloca = bool(inalloca_);
		type = getType(type_);

		// numelements_ is expected to be a LLVMTOK_COMMA node with a type_any child and a LLVMTOK_DECIMAL child.
		if (numelements_) {
			numelementsType = getType(numelements_->at(0));
			numelementsValue = getValue(numelements_->at(1));
		}

		if (align_)
			align = align_->atoi();

		if (addrspace_)
			addrspace = addrspace_->atoi();
	}

	std::string AllocaNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91malloca\e[0m";
		if (inalloca)
			out << " \e[38;5;202minalloca\e[0m";
		out << " " << *type;
		if (numelementsType)
			out << "\e[2m,\e[0m " << *numelementsType << " " << *numelementsValue;
		print(out, "\e[2m,\e[0;34m align\e[0m ", align);
		print(out, "\e[2m,\e[0;34m addrspace\e[0m(", addrspace, ")");
		return out.str();
	}

// StoreNode

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *source_, ASTNode *destination_, ASTNode *align_,
	                     ASTNode *bangs) {
		Deleter deleter(source_, destination_, volatile__, align_, bangs);
		atomic = false;
		source = std::make_shared<Constant>(source_);
		destination = std::make_shared<Constant>(destination_);

		volatile_ = bool(volatile__);

		if (align_)
			align = align_->atoi();

		handleBangs(bangs);
	}

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *source_, ASTNode *destination_, ASTNode *syncscope_,
	                     ASTNode *ordering_, ASTNode *align_, ASTNode *bangs) {
		Deleter deleter(source_, destination_, ordering_, align_, volatile__, syncscope_);
		atomic = true;
		source = std::make_shared<Constant>(source_);
		destination = std::make_shared<Constant>(destination_);
		align = align_->atoi();
		for (const std::pair<const Ordering, std::string> &pair: ordering_map)
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}

		volatile_ = bool(volatile__);

		if (syncscope_)
			syncscope = StringSet::intern(syncscope_->extractName());

		handleBangs(bangs);
	}

	void StoreNode::handleBangs(ASTNode *bangs) {
		debugIndex = bangs->debugIndex;
		handleUnibangs(bangs);
		for (const ASTNode *sub: *bangs) {
			if (sub->symbol == LLVMTOK_NONTEMPORAL)
				nontemporalIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_INVARIANT_GROUP)
				invariantGroupIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_TBAA)
				tbaa = sub->at(0)->atoi();
		}
	}

	std::string StoreNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91mstore\e[0m";
		if (atomic)
			out << " \e[38;5;202matomic\e[0m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[0m";
		out << "\e[0m " << *source << "\e[2m,\e[0m " << *destination;
		if (syncscope)
			out << " \e[34msyncscope\e[0;2m(\e[0m\"" << *syncscope << "\"\e[2m)\e[0m";
		if (align != -1)
			out << "\e[2m,\e[0;34m align \e[0m" << align;
		if (nontemporalIndex != -1)
			out << "\e[2m,\e[0;34m !nontemporal \e[0m" << nontemporalIndex;
		if (invariantGroupIndex != -1)
			out << "\e[2m,\e[0;34m !invariant.group \e[0m" << invariantGroupIndex;
		return out.str();
	}

	std::vector<ValuePtr> StoreNode::allValues() {
		return {source->convert()->value, destination->convert()->value};
	}

	std::vector<ValuePtr *> StoreNode::allValuePointers() {
		source = source->convert();
		destination = destination->convert();
		return {&source->value, &destination->value};
	}

// LoadNode

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *align_,
	                   ASTNode *bangs) {
		Deleter deleter(type_, constant_, volatile__, align_, bangs);
		atomic = false;
		result = result_->extracted();
		type = getType(type_);
		constant = std::make_shared<Constant>(constant_);
		volatile_ = bool(volatile__);

		if (align_)
			align = align_->atoi();

		handleBangs(bangs);
	}

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *syncscope_,
	                   ASTNode *ordering_, ASTNode *align_, ASTNode *bangs) {
		Deleter deleter(result_, type_, constant_, align_, ordering_, syncscope_, volatile__);
		atomic = true;
		result = result_->extracted();
		type = getType(type_);
		constant = std::make_shared<Constant>(constant_);
		align = align_->atoi();
		for (const std::pair<const Ordering, std::string> &pair: ordering_map)
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}

		if (syncscope_)
			syncscope = StringSet::intern(syncscope_->extractName());

		volatile_ = bool(volatile__);

		handleBangs(bangs);
	}

	void LoadNode::handleBangs(ASTNode *bangs) {
		debugIndex = bangs->debugIndex;
		handleUnibangs(bangs);
		for (const ASTNode *sub: *bangs) {
			if (sub->symbol == LLVMTOK_NONTEMPORAL)
				nontemporalIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_INVARIANT_LOAD)
				invariantLoadIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_INVARIANT_GROUP)
				invariantGroupIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_NONNULL)
				nonnullIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_DEREFERENCEABLE)
				dereferenceable = sub->at(0)->lexerInfo;
			else if (sub->symbol == LLVMTOK_DEREFERENCEABLE_OR_NULL)
				dereferenceableOrNull = sub->at(0)->lexerInfo;
			else if (sub->symbol == LLVMTOK_BANGALIGN)
				bangAlign = sub->at(0)->lexerInfo;
			else if (sub->symbol == LLVMTOK_TBAA)
				tbaa = sub->at(0)->atoi();
		}
	}

	std::string LoadNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91mload\e[0m";
		if (atomic)
			out << " \e[38;5;202matomic\e[0m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[0m";
		out << "\e[0m " << *type << "\e[2m,\e[0m " << *constant;
		if (syncscope)
			out << " \e[34msyncscope\e[0;2m(\e[0m\"" << *syncscope << "\"\e[2m)\e[0m";
		if (ordering != Ordering::None)
			out << " \e[38;5;202m" << ordering_map.at(ordering) << "\e[0m";
		if (align != -1)
			out << "\e[2m,\e[0;34m align \e[0m" << align;
		if (nontemporalIndex != -1)
			out << "\e[2m,\e[0;34m !nontemporal \e[0m" << nontemporalIndex;
		if (invariantGroupIndex != -1)
			out << "\e[2m,\e[0;34m !invariant.group \e[0m" << invariantGroupIndex;
		return out.str();
	}

// IcmpNode

	IcmpNode::IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op, ASTNode *const_,
	                   ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, cond_, type_, op, const_);
		handleUnibangs(unibangs);
		result = result_->extracted();

		for (const std::pair<const IcmpCond, std::string> &pair: cond_map)
			if (*cond_->lexerInfo == pair.second) {
				cond = pair.first;
				break;
			}

		type = getType(type_);
		left = getValue(op);
		right = std::make_shared<Constant>(const_, type);
	}

	std::string IcmpNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91micmp\e[0m " << cond_map.at(cond) << " " << *type << " "
		    << *left << ", " << *right;
		return out.str();
	}

	std::vector<ValuePtr> IcmpNode::allValues() {
		if (cachedConstantValue)
			return {left, cachedConstantValue};
		return {left, cachedConstantValue = right->convert()->value};
	}

	std::vector<ValuePtr *> IcmpNode::allValuePointers() {
		if (!cachedConstantValue)
			cachedConstantValue = right->convert()->value;
		return {&left, &cachedConstantValue};
	}

// BrUncondNode

	BrUncondNode::BrUncondNode(ASTNode *node, ASTNode *unibangs): BrUncondNode(node->lexerInfo) {
		Deleter deleter(node, unibangs);
		handleUnibangs(unibangs);
	}

	std::string BrUncondNode::debugExtra() const {
		return "\e[91mbr\e[0;34m label \e[32m" + *destination + "\e[0m";
	}

// BrCondNode

	BrCondNode::BrCondNode(ASTNode *type, ASTNode *condition_, ASTNode *if_true, ASTNode *if_false, ASTNode *unibangs) {
		Deleter deleter(unibangs, condition_, if_true, if_false);
		handleUnibangs(unibangs);
		if (*type->lexerInfo != "i1")
			llvmerror("Expected i1 for br condition type");
		condition = getValue(condition_);
		ifTrue = if_true->lexerInfo;
		ifFalse = if_false->lexerInfo;
	}

	std::string BrCondNode::debugExtra() const {
		return "\e[91mbr \e[33mi1\e[39m " + std::string(*condition) + ", label \e[32m" + *ifTrue + "\e[39m, label "
			"\e[32m" + *ifFalse + "\e[39m";
	}

// CallInvokeNode

	CallInvokeNode::CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
	                               ASTNode *attribute_list, ASTNode *unibangs) {
		Deleter deleter(unibangs, _result, _cconv, _retattrs, _addrspace, return_type, _args, function_name, _constants,
			attribute_list);
		handleUnibangs(unibangs);

		if (_result)
			result = StringSet::intern(_result->extractName());

		if (_cconv)
			cconv = _cconv->lexerInfo;

		if (_retattrs) {
			for (ASTNode *child: *_retattrs) {
				const std::string &raname = *child->lexerInfo;
				if (raname == "dereferenceable")
					dereferenceable = child->at(0)->atoi();
				else
					for (const std::pair<const RetAttr, std::string> &pair: retattr_map)
						if (raname == pair.second) {
							retattrs.insert(pair.first);
							break;
						}
			}
		}

		if (_addrspace)
			addrspace = _addrspace->at(0)->atoi();

		if (return_type)
			returnType = getType(return_type);

		if (_args) {
			argumentsExplicit = true;
			ASTNode *typelist = nullptr;
			if (_args->size() == 2) { // Both a typelist and an ellipsis are specified.
				argumentEllipsis = true;
				typelist = _args->at(0);
			} else if (_args->size() == 1) { // Either a typelist or an ellipsis is specified.
				if (_args->at(0)->symbol == LLVMTOK_ELLIPSIS)
					argumentEllipsis = true;
				else
					typelist = _args->at(0);
			}
			if (typelist)
				for (ASTNode *typenode: *typelist)
					argumentTypes.push_back(getType(typenode));
		}

		if (function_name) {
			name = getValue(function_name);
			if (!std::dynamic_pointer_cast<VariableValue>(name))
				throw std::runtime_error("Function name isn't a global or local variable");
		}

		if (_constants)
			for (ASTNode *child: *_constants)
				constants.push_back(std::make_shared<Constant>(child));

		if (attribute_list)
			for (ASTNode *child: *attribute_list)
				attributeIndices.push_back(child->atoi());
	}

	std::vector<ValuePtr> CallInvokeNode::allValues() {
		std::vector<ValuePtr> out;
		out.reserve(constants.size() + 1);
		for (ConstantPtr constant: constants)
			out.push_back(constant->value);
		if (std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(name))
			out.push_back(local);
		return out;
	}

	std::vector<ValuePtr *> CallInvokeNode::allValuePointers() {
		std::vector<ValuePtr *> out;
		out.reserve(constants.size() + 1);
		for (ConstantPtr &constant: constants)
			out.push_back(&constant->value);
		if (std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(name))
			out.push_back(&name);
		return out;
	}

	std::vector<ConstantPtr *> CallInvokeNode::allConstantPointers() {
		std::vector<ConstantPtr *> out;
		for (ConstantPtr &ptr: constants)
			out.push_back(&ptr);
		return out;
	}

// CallNode

	CallNode::CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs,
	                   ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *function_name,
	                   ASTNode *_constants, ASTNode *attribute_list, ASTNode *unibangs):
	                   CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, function_name,
	                                  _constants, attribute_list, unibangs) {
		Deleter deleter(_tail);
		if (_tail)
			tail = _tail->lexerInfo;
		getFastmath(fastmath, fastmath_flags);
	}

	std::string CallNode::debugExtra() const {
		std::stringstream out;
		if (result)
			out << getResult() << "\e[2m = ";
		print(out, "\e[0;34m", tail, " ");
		out << "\e[0;91mcall\e[0m" << fastmath;
		if (!fastmath.empty())
			out << "\e[0;2m .\e[0m";
		print(out, " \e[34m", cconv, "\e[0;2m .\e[0m");
		for (RetAttr attr: retattrs)
			out << " \e[34m" << retattr_map.at(attr) << "\e[0m";
		print(out, " \e[34mdereferenceable\e[0;2m(\e[0m", dereferenceable, "\e[2m)\e[0m");
		if (!retattrs.empty() || dereferenceable != -1)
			out << " \e[0;2m.\e[0m";
		print(out, " \e[34maddrspace\e[0;2m(\e[0m", addrspace, "\e[2m)\e[0m");
		out << " " << *returnType;
		if (argumentsExplicit) {
			out << " \e[1;2m(\e[0m";
			for (auto begin = argumentTypes.cbegin(), iter = begin, end = argumentTypes.cend(); iter != end; ++iter) {
				if (iter != begin)
					out << "\e[2m, \e[0m";
				out << **iter;
			}
			if (argumentEllipsis)
				out << "\e[2m" << (argumentTypes.empty()? "" : ", ") << "...\e[0m";
			out << "\e[1;2m)\e[0m";
		}
		out << " " << *name << "\e[2m(\e[0m";
		for (auto begin = constants.begin(), iter = begin, end = constants.end(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << **iter;
		}
		out << "\e[2m)\e[0m";
		return out.str();
	}

// AsmNode

	AsmNode::AsmNode(ASTNode *_result, ASTNode *_retattrs, ASTNode *return_type, ASTNode *_args, ASTNode *_sideeffect,
	                 ASTNode *_alignstack, ASTNode *_inteldialect, ASTNode *asm_string, ASTNode *asm_constraints,
	                 ASTNode *_constants, ASTNode *attribute_list, ASTNode *_srcloc, ASTNode *unibangs):
	                 CallInvokeNode(_result, nullptr, _retattrs, nullptr, return_type, _args, nullptr, _constants,
	                                attribute_list, unibangs) {
		Deleter deleter(asm_string, _sideeffect, _alignstack, _inteldialect, _srcloc, asm_constraints);
		contents = asm_string->lexerInfo;
		sideeffect = bool(_sideeffect);
		alignstack = bool(_alignstack);
		constraints = asm_constraints->lexerInfo;

		if (_srcloc)
			srcloc = _srcloc->atoi();
	}

	std::string AsmNode::debugExtra() const {
		return "???";
	}

// InvokeNode

	InvokeNode::InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                       ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
	                       ASTNode *attribute_list, ASTNode *normal_label, ASTNode *exception_label, ASTNode *unibangs):
	                       CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, function_name,
	                                      _constants, attribute_list, unibangs) {
		Deleter deleter(normal_label, exception_label);
		normalLabel = StringSet::intern(normal_label->extractName());
		exceptionLabel = StringSet::intern(exception_label->extractName());
	}

	std::string InvokeNode::debugExtra() const {
		std::stringstream out;
		if (result)
			out << getResult() << "\e[2m = ";
		out << "\e[0;91minvoke\e[0m";
		print(out, " \e[34m", cconv, "\e[0;2m .\e[0m");
		for (RetAttr attr: retattrs)
			out << " \e[34m" << retattr_map.at(attr) << "\e[0m";
		if (dereferenceable != -1)
			out << " \e[34mdereferenceable\e[0;2m(\e[0m" << dereferenceable << "\e[2m)\e[0m";
		if (!retattrs.empty() || dereferenceable != -1)
			out << " \e[0;2m.\e[0m";
		if (addrspace != -1)
			out << " \e[34maddrspace\e[0;2m(\e[0m" << addrspace << "\e[2m)\e[0m";
		out << " " << *returnType;
		if (argumentsExplicit) {
			out << " \e[1;2m(\e[0m";
			for (auto begin = argumentTypes.cbegin(), iter = begin, end = argumentTypes.cend(); iter != end; ++iter) {
				if (iter != begin)
					out << "\e[2m, \e[0m";
				out << **iter;
			}
			if (argumentEllipsis)
				out << "\e[2m" << (argumentTypes.empty()? "" : ", ") << "...\e[0m";
			out << "\e[1;2m)\e[0m";
		}
		out << " " << *name << "\e[2m(\e[0m";
		for (auto begin = constants.begin(), iter = begin, end = constants.end(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << **iter;
		}
		out << "\e[2m)\e[0;91m to \e[34mlabel %" << *normalLabel << " \e[91munwind\e[34m label %" << *exceptionLabel
		    << "\e[0m";
		return out.str();
	}

// GetelementptrNode

	GetelementptrNode::GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *constant_,
	                                     ASTNode *indices_, ASTNode *unibangs) {
		Deleter deleter(unibangs, _inbounds, pvar, type_, constant_, indices_);
		handleUnibangs(unibangs);
		result = StringSet::intern(pvar->extractName());
		inbounds = bool(_inbounds);
		type = getType(type_);
		constant = std::make_shared<Constant>(constant_);

		for (const ASTNode *comma: *indices_) {
			const long width = comma->at(0)->atoi(1);
			const ASTNode &index = *comma->at(1);
			const bool has_minrange = comma->size() == 3;
			if (index.symbol == LLVMTOK_PVAR)
				indices.emplace_back(width, StringSet::intern(index.lexerInfo->substr(1)), has_minrange, true);
			else
				indices.emplace_back(width, index.atoi(), has_minrange, false);
		}
	}

	std::string GetelementptrNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << " \e[2m= \e[0;91mgetelementptr\e[0m ";
		if (inbounds)
			out << "\e[34minbounds\e[0m ";
		out << *type << "\e[2m,\e[0m " << *constant << "\e[0m";
		for (auto [width, value, minrange, pvar]: indices) {
			out << "\e[2m,\e[0m ";
			if (minrange)
				out << "\e[34minrange\e[0m ";
			out << "\e[33mi" << width << "\e[0m ";
			if (pvar)
				out << "\e[32m%";
			if (std::holds_alternative<long>(value))
				out << std::get<long>(value) << "\e[0m";
			else
				out << *std::get<Variable::ID>(value) << "\e[0m";
		}
		return out.str();
	}

	std::vector<ValuePtr> GetelementptrNode::allValues() {
		if (!cachedConstantValue)
			cachedConstantValue = constant->convert()->value;
		return {cachedConstantValue};
	}

	std::vector<ValuePtr *> GetelementptrNode::allValuePointers() {
		if (!cachedConstantValue)
			cachedConstantValue = constant->convert()->value;
		return {&cachedConstantValue};
	}

// RetNode

	RetNode::RetNode(ASTNode *unibangs): type(std::make_shared<VoidType>()), value(std::make_shared<VoidValue>()) {
		Deleter deleter(unibangs);
		handleUnibangs(unibangs);
	}

	RetNode::RetNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs) {
		Deleter deleter(unibangs, type_, value_);
		handleUnibangs(unibangs);
		type = getType(type_);
		value = getValue(value_);
	}

	std::string RetNode::debugExtra() const {
		const std::string type_str = *type;
		return "\e[91mret\e[0m " + (type_str != "void"? type_str + " " + std::string(*value) : type_str);
	}

// LandingpadNode

	LandingpadNode::Clause::Clause(ASTNode *node) {
		clauseType = node->symbol == LLVMTOK_CATCH? ClauseType::Catch : ClauseType::Filter;
		if (node->at(0)->symbol == LLVM_ARRAY_VALUE) {
			type = getType(node->at(0)->at(0));
			value = getValue(node->at(0)->at(1));
		} else {
			type = getType(node->at(0));
			value = getValue(node->at(1));
		}
	}

	LandingpadNode::Clause::operator std::string() const {
		return (clauseType == ClauseType::Catch? "catch" : "filter") + (type? " " + std::string(*type) : "") + " " +
			std::string(*value);
	}

	LandingpadNode::LandingpadNode(ASTNode *result_, ASTNode *type_, ASTNode *clauses_, ASTNode *unibangs,
	                               bool cleanup_) {
		Deleter deleter(unibangs, result_, type_, clauses_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		type = getType(type_);
		for (ASTNode *clause: *clauses_)
			clauses.push_back(std::make_shared<Clause>(clause));
		cleanup = cleanup_;
	}

	std::string LandingpadNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91mlandingpad\e[0m " << *type;
		if (cleanup)
			out << " cleanup";
		for (std::shared_ptr<Clause> clause: clauses)
			out << " " << std::string(*clause);
		return out.str();
	}

	std::vector<ValuePtr> LandingpadNode::allValues() {
		std::vector<ValuePtr> out;
		out.reserve(clauses.size());
		for (std::shared_ptr<Clause> clause: clauses)
			out.push_back(clause->value);
		return out;
	}

	std::vector<ValuePtr *> LandingpadNode::allValuePointers() {
		std::vector<ValuePtr *> out;
		out.reserve(clauses.size());
		for (std::shared_ptr<Clause> &clause: clauses)
			out.push_back(&clause->value);
		return out;
	}

// ConversionNode

	ConversionNode::ConversionNode(ASTNode *result_, ASTNode *conv_op, ASTNode *from_, ASTNode *value_, ASTNode *to_,
	                               ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, conv_op, from_, value_, to_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		from = getType(from_);
		value = getValue(value_);
		to = getType(to_);
		for (const std::pair<const Conversion, std::string> &pair: conversion_map)
			if (*conv_op->lexerInfo == pair.second) {
				conversionType = pair.first;
				break;
			}
	}

	std::string ConversionNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91m" << conversion_map.at(conversionType) << "\e[0m " << *from
		    << " " << *value << " \e[91mto\e[0m " << *to;
		return out.str();
	}

// BasicMathNode

	BasicMathNode::BasicMathNode(ASTNode *result_, ASTNode *oper_, bool nuw_, bool nsw_, ASTNode *type_,
	                             ASTNode *left_, ASTNode *right_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, oper_, type_, left_, right_);
		handleUnibangs(unibangs);
		oper = oper_->lexerInfo;
		operSymbol = oper_->symbol;
		result = result_->extracted();
		nuw = nuw_;
		nsw = nsw_;
		type = getType(type_);
		left = getValue(left_);
		right = getValue(right_);
	}

	std::string BasicMathNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91m" << *oper << " " << *type << " " << *left << "\e[2m,\e[0m "
		    << *right;
		return out.str();
	}

// PhiNode

	PhiNode::PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, type_, pairs_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		type = getType(type_);
		getFastmath(fastmath, fastmath_);
		for (ASTNode *node: *pairs_) {
			ValuePtr value = getValue(node->at(0));
			pairs.push_back({value, node->at(1)->extracted()});
			if (!value->isLocal())
				pure = false;
		}
	}

	std::string PhiNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << " \e[0;2m= \e[0;91mphi\e[0m" << fastmath << " " << *type;
		for (const std::pair<ValuePtr, const std::string *> &pair: pairs)
			out << " \e[2m[\e[0m" << *pair.first << "\e[2m,\e[0;32m %" << *pair.second << "\e[0;2m]\e[0m";
		return out.str();
	}

	std::vector<ValuePtr> PhiNode::allValues() {
		std::vector<ValuePtr> out;
		for (const std::pair<ValuePtr, const std::string *> &pair: pairs)
			out.push_back(pair.first);
		return out;
	}

	std::vector<ValuePtr *> PhiNode::allValuePointers() {
		std::vector<ValuePtr *> out;
		for (std::pair<ValuePtr, const std::string *> &pair: pairs)
			out.push_back(&pair.first);
		return out;
	}

// SimpleNode

	SimpleNode::SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, type_, left_, right_);
		handleUnibangs(unibangs);
		locate(result_);
		result = result_->extracted();
		type = getType(type_);
		left = getValue(left_);
		right = getValue(right_);
	}

	std::string SimpleNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91m" << typeName() << "\e[0m " << *type << " " << *left
		    << "\e[2m,\e[0m " << *right;
		return out.str();
	}

// DivNode

	DivNode::DivNode(ASTNode *result_, ASTNode *div, ASTNode *exact_,  ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		Deleter deleter(exact_, div);
		exact = bool(exact_);
		divType = *div->lexerInfo == "sdiv"? DivType::Sdiv : DivType::Udiv;
	}

// RemNode

	RemNode::RemNode(ASTNode *result_, ASTNode *rem, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		Deleter deleter(exact_, rem);
		exact = bool(exact_);
		remType = *rem->lexerInfo == "srem"? RemType::Srem : RemType::Urem;
	}

// LogicNode

	LogicNode::LogicNode(ASTNode *result_, ASTNode *logic, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                     ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		Deleter deleter(logic);
		if (*logic->lexerInfo == "and") logicType = LogicType::And;
		else if (*logic->lexerInfo == "or") logicType = LogicType::Or;
		else if (*logic->lexerInfo == "xor") logicType = LogicType::Xor;
		else throw std::invalid_argument("Invalid LogicType: \"" + *logic->lexerInfo + "\"");
	}

	const char * LogicNode::typeName() const {
		switch (logicType) {
			case LogicType::And: return "and";
			case LogicType::Or:  return "or";
			case LogicType::Xor: return "xor";
			default: throw std::invalid_argument("Invalid LogicType: " + std::to_string(static_cast<int>(logicType)));
		}
	}

// ShrNode

	ShrNode::ShrNode(ASTNode *result_, ASTNode *shr, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		Deleter deleter(exact_, shr);
		exact = bool(exact_);
		shrType = *shr->lexerInfo == "lshr"? ShrType::Lshr : ShrType::Ashr;
	}

// FMathNode

	FMathNode::FMathNode(ASTNode *result_, ASTNode *fmath, ASTNode *flags, ASTNode *type_, ASTNode *left_,
	                     ASTNode *right_, ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		const std::string &fmath_name = *fmath->lexerInfo;
		Deleter deleter(fmath, flags);
		if (fmath_name == "fadd") fmathType = FMathType::Fadd;
		else if (fmath_name == "fsub") fmathType = FMathType::Fsub;
		else if (fmath_name == "fmul") fmathType = FMathType::Fmul;
		else if (fmath_name == "fdiv") fmathType = FMathType::Fdiv;
		else if (fmath_name == "frem") fmathType = FMathType::Frem;
		else throw std::invalid_argument("Invalid FMathType: \"" + fmath_name + "\"");
		getFastmath(fastmath, flags);
	}

	const char * FMathNode::typeName() const {
		switch (fmathType) {
			case FMathType::Fadd: return "fadd";
			case FMathType::Fsub: return "fsub";
			case FMathType::Fmul: return "fmul";
			case FMathType::Fdiv: return "fdiv";
			case FMathType::Frem: return "frem";
			default: throw std::invalid_argument("Invalid FMathType: " + std::to_string(static_cast<int>(fmathType)));
		}
	}

	std::string FMathNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[2m = \e[0;91m" << typeName() << fastmath << "\e[0m " << *type << " " << *left
		    << "\e[2m,\e[0m " << *right;
		return out.str();
	}

// SwitchNode

	SwitchNode::SwitchNode(ASTNode *type_, ASTNode *value_, ASTNode *label_, ASTNode *table_, ASTNode *unibangs) {
		Deleter deleter(unibangs, type_, value_, label_, table_);
		handleUnibangs(unibangs);
		type = getType(type_);
		value = getValue(value_);
		label = label_->extracted();
		table.reserve(table_->size());
		for (ASTNode *comma: *table_)
			table.push_back({getType(comma->at(0)), getValue(comma->at(1)), comma->at(2)->extracted()});
	}

	std::string SwitchNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91mswitch\e[0m " << *type << " " << *value << "\e[2m,\e[0;34m label %" << *label << " \e[0;2m[\e[0m";
		for (auto begin = table.cbegin(), iter = begin, end = table.cend(); iter != end; ++iter) {
			if (iter != begin)
				out << " ";
			const std::tuple<TypePtr, ValuePtr, const std::string *> &tuple = *iter;
			out << *std::get<0>(tuple) << " " << *std::get<1>(tuple) << ", \e[34mlabel %" << *std::get<2>(tuple)
			    << "\e[0m";
		}
		out << "\e[2m]\e[0m";
		return out.str();
	}

// ExtractValueNode

	ExtractValueNode::ExtractValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value,
	                                   ASTNode *decimals_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, aggregate_type, aggregate_value, decimals_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		TypePtr uncasted = getType(aggregate_type);
		aggregateType = std::dynamic_pointer_cast<AggregateType>(uncasted);
		if (!aggregateType) {
			throw std::runtime_error("Type of extractvalue instruction isn't an aggregate type: " +
				std::string(*uncasted));
		}
		aggregateValue = getValue(aggregate_value);
		for (ASTNode *decimal: *decimals_)
			decimals.push_back(decimal->atoi());
	}

	std::string ExtractValueNode::debugExtra() const {
		std::stringstream out;
		out << "\e[34m%" << *result << " \e[39;2m= \e[22;91mextractvalue\e[39m " << *aggregateType << " "
		    << *aggregateValue;
		for (int decimal: decimals)
			out << "\e[2m,\e[0m " << decimal;
		return out.str();
	}

// InsertValueNode

	InsertValueNode::InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value,
	                                 ASTNode *type_, ASTNode *value_, ASTNode *decimals_, ASTNode *unibangs) {
		Deleter deleter(unibangs, aggregate_type, aggregate_value, type_, value_, decimals_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		aggregateType = getType(aggregate_type);
		aggregateValue = getValue(aggregate_value);
		type = getType(type_);
		value = getValue(value_);
		for (ASTNode *decimal: *decimals_)
			decimals.push_back(decimal->atoi());
	}

	std::string InsertValueNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91minsertvalue\e[0m " << *aggregateType << " " << *aggregateValue << "\e[2m,\e[0m " << *type << " "
		    << *value;
		for (int decimal: decimals)
			out << "\e[2m,\e[0m " << decimal;
		return out.str();
	}

// ResumeNode

	ResumeNode::ResumeNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs) {
		Deleter deleter(unibangs, type_, value_);
		handleUnibangs(unibangs);
		type = getType(type_);
		value = getValue(value_);
	}

	std::string ResumeNode::debugExtra() const {
		return "\e[91mresume\e[0m " + std::string(*type) + " " + std::string(*value);
	}

// FreezeNode

	FreezeNode::FreezeNode(ASTNode *result_, ASTNode *type_, ASTNode *value_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, type_, value_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		type = getType(type_);
		value = getValue(value_);
	}

	std::string FreezeNode::debugExtra() const {
		return "\e[34m%" + std::string(*result) + " \e[39;2m= \e[22;91mfreeze\e[39m " + std::string(*type) + ' ' +
			std::string(*value) + '\n';
	}

	ASTNode * ignoreConversion(ASTNode *node) {
		if (*node->lexerInfo != "bitcast")
			throw std::invalid_argument("Unexpected conversion expr in ignoreConversion: " + *node->lexerInfo);
		return node->at(0)->at(1);
	}
}
