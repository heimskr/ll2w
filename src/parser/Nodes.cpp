#include <iostream>
#include <sstream>

#include "compiler/Variable.h"
#include "parser/Lexer.h"
#include "parser/Nodes.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "parser/Util.h"
#include "util/Util.h"

namespace LL2W {

// MetadataDef

	MetadataDef::MetadataDef(ASTNode *dotident_node, ASTNode *distinct_node, ASTNode *list):
		BaseNode(llvmParser, LLVMTOK_METADATA, StringSet::intern(dotident_node->concatenate().c_str())) {
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
		delete node;
	}

	HeaderNode::HeaderNode(ASTNode *node): BaseNode(llvmParser, LLVM_BLOCKHEADER, "") {
		locate(node);
		label = StringSet::intern(node->lexerInfo->substr(0, node->lexerInfo->size() - 1));
		delete node;
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
		index = node->at(0)->atoi();
		for (ASTNode *child: *node->at(1)) {
			if (child->symbol == LLVMTOK_FNATTR_BASIC) {
				for (const std::pair<const FnAttr, std::string> &pair: fnattr_map) {
					if (*child->lexerInfo == pair.second) {
						basicAttributes.insert(pair.first);
						break;
					}
				}
			} else if (child->symbol == LLVMTOK_STRING) {
				stringAttributes.insert({child->extracted(), StringSet::intern("")});
			} else if (child->symbol == LLVMTOK_EQUALS) {
				stringAttributes.insert({child->at(0)->extracted(), child->at(1)->extracted()});
			} else if (child->symbol == LLVMTOK_ALLOCSIZE) {
				allocsizeSize = child->at(0)->atoi();
				if (1 < child->size())
					allocsizeCount = child->at(1)->atoi();
			} else {
				node->at(1)->debug();
				throw std::runtime_error("Invalid child of ATTRIBUTE_LIST: " + std::string(child->getName()));
			}
		}
		delete node;
	}

	std::string AttributesNode::debugExtra() const {
		std::stringstream out;
		out << "attributes #\e[92m" << index << "\e[0m \e[2m= { \e[0m";
		for (FnAttr attr: basicAttributes)
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
				prof = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_CALLEES)
				callees = sub->at(0)->atoi();
		}
	}

// Reader

	std::vector<std::shared_ptr<LocalValue>> Reader::allLocals() const {
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

// SelectNode

	SelectNode::SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type, ASTNode *condition_value,
	                       ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();
		getFastmath(fastmath, fastmath_);
		conditionType = getType(condition_type);
		conditionValue = getValue(condition_value);
		firstType = getType(type1);
		firstValue = getValue(val1);
		secondType = getType(type2);
		secondValue = getValue(val2);

		delete result_;
		delete condition_type;
		delete condition_value;
		delete type1;
		delete val1;
		delete type2;
		delete val2;
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
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();
		delete result_;

		if (inalloca_) {
			inalloca = true;
			delete inalloca_;
		}

		type = getType(type_);
		delete type_;

		// numelements_ is expected to be a LLVMTOK_COMMA node with a type_any child and a LLVMTOK_DECIMAL child.
		if (numelements_) {
			numelementsType = getType(numelements_->at(0));
			numelementsValue = getValue(numelements_->at(1));
			delete numelements_;
		}

		if (align_) {
			align = align_->atoi();
			delete align_;
		}

		if (addrspace_) {
			addrspace = addrspace_->atoi();
			delete addrspace_;
		}
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
		atomic = false;
		source = std::make_shared<Constant>(source_);
		destination = std::make_shared<Constant>(destination_);

		delete source_;
		delete destination_;

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		if (align_) {
			align = align_->atoi();
			delete align_;
		}

		handleBangs(bangs);
	}

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *source_, ASTNode *destination_, ASTNode *syncscope_,
	                     ASTNode *ordering_, ASTNode *align_, ASTNode *bangs) {
		atomic = true;
		source = std::make_shared<Constant>(source_);
		destination = std::make_shared<Constant>(destination_);
		align = align_->atoi();
		for (const std::pair<const Ordering, std::string> &pair: ordering_map) {
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}
		}

		delete source_;
		delete destination_;
		delete ordering_;
		delete align_;

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		if (syncscope_) {
			syncscope = StringSet::intern(syncscope_->extractName());
			delete syncscope_;
		}

		handleBangs(bangs);
	}

	void StoreNode::handleBangs(ASTNode *bangs) {
		handleUnibangs(bangs);
		for (const ASTNode *sub: *bangs) {
			if (sub->symbol == LLVMTOK_NONTEMPORAL)
				nontemporalIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_INVARIANT_GROUP)
				invariantGroupIndex = sub->at(0)->atoi();
			else if (sub->symbol == LLVMTOK_TBAA)
				tbaa = sub->at(0)->atoi();
		}

		delete bangs;
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

	std::vector<ValuePtr> StoreNode::allValues() const {
		return {source->convert()->value, destination->convert()->value};
	}

	std::vector<ValuePtr *> StoreNode::allValuePointers() {
		if (!cachedSourceValue)
			cachedSourceValue = source->convert()->value;
		if (!cachedDestinationValue)
			cachedDestinationValue = destination->convert()->value;
		return {&cachedSourceValue, &cachedDestinationValue};
	}

// LoadNode

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *align_,
	                   ASTNode *bangs) {
		atomic = false;
		result = result_->extracted();
		type = getType(type_);
		constant = std::make_shared<Constant>(constant_);

		delete type_;
		delete constant_;

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		if (align_) {
			align = align_->atoi();
			delete align_;
		}

		handleBangs(bangs);
	}

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *syncscope_,
	                   ASTNode *ordering_, ASTNode *align_, ASTNode *bangs) {
		atomic = true;
		result = result_->extracted();
		type = getType(type_);
		constant = std::make_shared<Constant>(constant_);
		align = align_->atoi();
		for (const std::pair<const Ordering, std::string> &pair: ordering_map) {
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}
		}

		delete result_;
		delete type_;
		delete constant_;
		delete align_;
		delete ordering_;

		if (syncscope_) {
			syncscope = StringSet::intern(syncscope_->extractName());
			delete syncscope_;
		}

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		handleBangs(bangs);
	}

	void LoadNode::handleBangs(ASTNode *bangs) {
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

		delete bangs;
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

	IcmpNode::IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op1, ASTNode *op2,
	                   ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();

		for (const std::pair<const IcmpCond, std::string> &pair: cond_map) {
			if (*cond_->lexerInfo == pair.second) {
				cond = pair.first;
				break;
			}
		}

		type = getType(type_);
		value1 = getValue(op1);
		value2 = getValue(op2);

		delete result_;
		delete cond_;
		delete type_;
		delete op1;
		delete op2;
	}

	std::string IcmpNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91micmp\e[0m " << cond_map.at(cond) << " " << *type << " "
		    << *value1 << ", " << *value2;
		return out.str();
	}

// BrUncondNode

	BrUncondNode::BrUncondNode(ASTNode *node, ASTNode *unibangs): BrUncondNode(node->lexerInfo) {
		handleUnibangs(unibangs);
		delete node;
		delete unibangs;
	}

	std::string BrUncondNode::debugExtra() const {
		return "\e[91mbr\e[0;34m label \e[32m" + *destination + "\e[0m";
	}

// BrCondNode

	BrCondNode::BrCondNode(ASTNode *type, ASTNode *condition_, ASTNode *if_true, ASTNode *if_false, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;
		if (*type->lexerInfo != "i1")
			llvmerror("Expected i1 for br condition type");
		condition = getValue(condition_);
		ifTrue = if_true->lexerInfo;
		ifFalse = if_false->lexerInfo;

		delete condition_;
		delete if_true;
		delete if_false;
	}

	std::string BrCondNode::debugExtra() const {
		return "\e[91mbr \e[33mi1\e[39m " + std::string(*condition) + ", label \e[32m" + *ifTrue + "\e[39m, label "
			"\e[32m" + *ifFalse + "\e[39m";
	}

// CallInvokeNode

	CallInvokeNode::CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
	                               ASTNode *attribute_list, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;

		if (_result) {
			result = StringSet::intern(_result->extractName());
			delete _result;
		}

		if (_cconv) {
			cconv = _cconv->lexerInfo;
			delete _cconv;
		}

		if (_retattrs) {
			for (ASTNode *child: *_retattrs) {
				const std::string &raname = *child->lexerInfo;
				if (raname == "dereferenceable") {
					dereferenceable = child->at(0)->atoi();
				} else {
					for (const std::pair<const RetAttr, std::string> &pair: retattr_map) {
						if (raname == pair.second) {
							retattrs.insert(pair.first);
							break;
						}
					}
				}
			}
			delete _retattrs;
		}

		if (_addrspace) {
			addrspace = _addrspace->at(0)->atoi();
			delete _addrspace;
		}

		if (return_type) {
			returnType = getType(return_type);
			delete return_type;
		}

		if (_args) {
			argumentsExplicit = true;
			ASTNode *typelist = nullptr;
			if (_args->size() == 2) { // Both a typelist and an ellipsis are specified.
				argumentEllipsis = true;
				typelist = _args->at(0);
			} else if (_args->size() == 1) { // Either a typelist or an ellipsis is specified.
				if (_args->at(0)->symbol == LLVMTOK_ELLIPSIS) {
					argumentEllipsis = true;
				} else {
					typelist = _args->at(0);
				}
			}
			if (typelist) {
				for (ASTNode *typenode: *typelist)
					argumentTypes.push_back(getType(typenode));
			}
			delete _args;
		}

		if (function_name) {
			name = getValue(function_name);
			delete function_name;
			if (!std::dynamic_pointer_cast<VariableValue>(name)) {
				if (_constants)
					delete _constants;
				delete attribute_list;
				throw std::runtime_error("Function name isn't a global or local variable");
			}
		}

		if (_constants) {
			for (ASTNode *child: *_constants)
				constants.push_back(std::make_shared<Constant>(child));
			delete _constants;
		}

		if (attribute_list) {
			for (ASTNode *child: *attribute_list)
				attributeIndices.push_back(child->atoi());
			delete attribute_list;
		}
	}

	std::vector<ValuePtr> CallInvokeNode::allValues() const {
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

// CallNode

	CallNode::CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs,
	                   ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *function_name,
	                   ASTNode *_constants, ASTNode *attribute_list, ASTNode *unibangs):
	                   CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, function_name,
	                                  _constants, attribute_list, unibangs) {
		if (_tail) {
			tail = _tail->lexerInfo;
			delete _tail;
		}

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
		contents = asm_string->lexerInfo;
		delete asm_string;

		if (_sideeffect) {
			sideeffect = true;
			delete _sideeffect;
		}

		if (_alignstack) {
			alignstack = true;
			delete _alignstack;
		}

		if (_inteldialect)
			delete _inteldialect;

		if (_srcloc) {
			srcloc = _srcloc->atoi();
			delete _srcloc;
		}

		constraints = asm_constraints->lexerInfo;
		delete asm_constraints;
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
		normalLabel = StringSet::intern(normal_label->extractName());
		delete normal_label;

		exceptionLabel = StringSet::intern(exception_label->extractName());
		delete exception_label;
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

	GetelementptrNode::GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *ptr_type,
	                                     ASTNode *ptr_value, ASTNode *indices_, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;
		result = StringSet::intern(pvar->extractName());
		if (_inbounds) {
			inbounds = true;
			delete _inbounds;
		}
		type = getType(type_);
		ptrType = getType(ptr_type);
		if (ptr_value->symbol == LLVMTOK_PVAR) {
			const std::string extracted = ptr_value->extractName();
			if (!Util::isNumeric(extracted)) {
				llvmerror("Non-numeric pointer encountered in getelementptr instruction: " + extracted,
					ptr_value->location);
			}
		} else if (ptr_value->symbol != LLVMTOK_GVAR) {
			llvmerror("Invalid pointer symbol in getelementptr instruction: " +
				std::string(llvmParser.getName(ptr_value->symbol)), ptr_value->location);
		}

		ptrValue = getValue(ptr_value);
		if (!std::dynamic_pointer_cast<LocalValue>(ptrValue) && !std::dynamic_pointer_cast<GlobalValue>(ptrValue))
			llvmerror("Expected LocalValue or GlobalValue in getelementptr instruction", ptr_value->location);

		for (ASTNode *comma: *indices_) {
			indices.push_back({
				comma->at(0)->atoi(1),
				comma->at(1)->atoi(),
				comma->size() == 3,
				comma->at(1)->symbol == LLVMTOK_PVAR});
		}

		delete pvar;
		delete type_;
		delete ptr_type;
		delete ptr_value;
		delete indices_;
	}

	std::string GetelementptrNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << " \e[2m= \e[0;91mgetelementptr\e[0m ";
		if (inbounds)
			out << "\e[34minbounds\e[0m ";
		out << *type << "\e[2m,\e[0m " << *ptrType << " " << *ptrValue << "\e[0m";
		for (auto [width, value, minrange, pvar]: indices) {
			out << "\e[2m,\e[0m ";
			if (minrange)
				out << "\e[34minrange\e[0m ";
			out << "\e[33mi" << width << "\e[0m ";
			if (pvar)
				out << "\e[32m%";
			out << value << "\e[0m";
		}
		return out.str();
	}

// RetNode

	RetNode::RetNode(ASTNode *unibangs): type(std::make_shared<VoidType>()), value(std::make_shared<VoidValue>()) {
		handleUnibangs(unibangs);
		delete unibangs;
	}

	RetNode::RetNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;

		type = getType(type_);
		value = getValue(value_);

		delete type_;
		delete value_;
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
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();
		type = getType(type_);
		for (ASTNode *clause: *clauses_) {
			clauses.push_back(std::make_shared<Clause>(clause));
		}
		cleanup = cleanup_;

		delete result_;
		delete type_;
		delete clauses_;
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

	std::vector<ValuePtr> LandingpadNode::allValues() const {
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
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();
		from = getType(from_);
		value = getValue(value_);
		to = getType(to_);
		for (const std::pair<const Conversion, std::string> &pair: conversion_map) {
			if (*conv_op->lexerInfo == pair.second) {
				conversionType = pair.first;
				break;
			}
		}

		delete result_;
		delete conv_op;
		delete from_;
		delete value_;
		delete to_;
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
		handleUnibangs(unibangs);
		delete unibangs;
		oper = oper_->lexerInfo;
		operSymbol = oper_->symbol;
		result = result_->extracted();
		nuw = nuw_;
		nsw = nsw_;
		type = getType(type_);
		left = getValue(left_);
		right = getValue(right_);

		delete result_;
		delete oper_;
		delete type_;
		delete left_;
		delete right_;
	}

	std::string BasicMathNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91m" << *oper << " " << *type << " " << *left << "\e[2m,\e[0m "
		    << *right;
		return out.str();
	}

// PhiNode

	PhiNode::PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();
		type = getType(type_);
		getFastmath(fastmath, fastmath_);
		for (ASTNode *node: *pairs_) {
			ValuePtr value = getValue(node->at(0));
			pairs.push_back({value, node->at(1)->extracted()});
			if (!value->isLocal())
				pure = false;
		}

		delete result_;
		delete type_;
		delete pairs_;
	}

	std::string PhiNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << " \e[0;2m= \e[0;91mphi\e[0m" << fastmath << " " << *type;
		for (const std::pair<ValuePtr, const std::string *> &pair: pairs)
			out << " \e[2m[\e[0m" << *pair.first << "\e[2m,\e[0;32m %" << *pair.second << "\e[0;2m]\e[0m";
		return out.str();
	}

	std::vector<ValuePtr> PhiNode::allValues() const {
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
		handleUnibangs(unibangs);
		delete unibangs;
		locate(result_);
		result = result_->extracted();
		type = getType(type_);
		left = getValue(left_);
		right = getValue(right_);

		delete result_;
		delete type_;
		delete left_;
		delete right_;
	}

	std::string SimpleNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91m" << typeName() << "\e[0m " << *type << " " << *left
		    << "\e[2m,\e[0m " << *right;
		return out.str();
	}

// DivNode

	DivNode::DivNode(ASTNode *result_, ASTNode *div, ASTNode *exact_,  ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs):
	SimpleNode(result_, type_, left_, right_, unibangs) {
		if (exact_) {
			exact = true;
			delete exact_;
		}
		divType = *div->lexerInfo == "sdiv"? DivType::Sdiv : DivType::Udiv;
	}

// RemNode

	RemNode::RemNode(ASTNode *result_, ASTNode *rem, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs):
	SimpleNode(result_, type_, left_, right_, unibangs) {
		if (exact_) {
			exact = true;
			delete exact_;
		}
		remType = *rem->lexerInfo == "srem"? RemType::Srem : RemType::Urem;
	}

// LogicNode

	LogicNode::LogicNode(ASTNode *result_, ASTNode *logic, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                     ASTNode *unibangs):
	SimpleNode(result_, type_, left_, right_, unibangs) {
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
	                 ASTNode *unibangs):
		SimpleNode(result_, type_, left_, right_, unibangs) {
		shrType = *shr->lexerInfo == "lshr"? ShrType::Lshr : ShrType::Ashr;
		if (exact_) {
			exact = true;
			delete exact_;
		}
	}

// FMathNode

	FMathNode::FMathNode(ASTNode *result_, ASTNode *fmath, ASTNode *flags, ASTNode *type_, ASTNode *left_,
	                     ASTNode *right_, ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		if (*fmath->lexerInfo == "fadd") fmathType = FMathType::Fadd;
		else if (*fmath->lexerInfo == "fsub") fmathType = FMathType::Fsub;
		else if (*fmath->lexerInfo == "fmul") fmathType = FMathType::Fmul;
		else if (*fmath->lexerInfo == "fdiv") fmathType = FMathType::Fdiv;
		else if (*fmath->lexerInfo == "frem") fmathType = FMathType::Frem;
		else throw std::invalid_argument("Invalid FMathType: \"" + *fmath->lexerInfo + "\"");
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
		handleUnibangs(unibangs);
		delete unibangs;
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
		handleUnibangs(unibangs);
		delete unibangs;
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

		delete result_;
		delete aggregate_type;
		delete aggregate_value;
		delete decimals_;
	}

	std::string ExtractValueNode::debugExtra() const {
		std::stringstream out;
		out << "\e[34m%" << *result << " \e[0;2m= \e[0;91mextractvalue\e[0m " << *aggregateType << " "
		    << *aggregateValue;
		for (int decimal: decimals)
			out << "\e[2m,\e[0m " << decimal;
		return out.str();
	}

// InsertValueNode

	InsertValueNode::InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value,
	                                 ASTNode *type_, ASTNode *value_, ASTNode *decimals_, ASTNode *unibangs) {
		handleUnibangs(unibangs);
		delete unibangs;
		result = result_->extracted();
		aggregateType = getType(aggregate_type);
		aggregateValue = getValue(aggregate_value);
		type = getType(type_);
		value = getValue(value_);
		for (ASTNode *decimal: *decimals_)
			decimals.push_back(decimal->atoi());

		delete aggregate_type;
		delete aggregate_value;
		delete type_;
		delete value_;
		delete decimals_;
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
		handleUnibangs(unibangs);
		delete unibangs;
		type = getType(type_);
		value = getValue(value_);
	}

	std::string ResumeNode::debugExtra() const {
		return "\e[91mresume\e[0m " + std::string(*type) + " " + std::string(*value);
	}
}
