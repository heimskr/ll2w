#include "compiler/Variable.h"
#include "parser/EnumConversion.h"
#include "parser/Lexer.h"
#include "parser/Nodes.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "parser/Util.h"
#include "util/Deleter.h"
#include "util/Util.h"

#include <llvm/IR/FMF.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_os_ostream.h>

#include <iostream>
#include <sstream>

namespace LL2W {

// MetadataDef

	MetadataDef::MetadataDef(ASTNode *dotident_node, ASTNode *distinct_node, ASTNode *list):
		BaseNode(llvmParser, LLVM_METADATA, StringSet::intern(dotident_node->concatenate().c_str())) {
		locate(dotident_node);
		if ((distinct = distinct_node != nullptr))
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
			label = node->symbol == LLVMTOK_STRING? node->extracted() : node->lexerInfo;
			list = node->at(1);
		} else {
			const auto at0 = node->at(0);
			label = at0->symbol == LLVMTOK_STRING? at0->extracted() : at0->lexerInfo;
			list = node->at(2);
		}

		preds.reserve(list->size());
		for (const ASTNode *pred: *list) {
			const std::string &pred_label = *pred->lexerInfo;
			if (pred_label[1] == '"')
				preds.push_back(StringSet::intern(pred_label.substr(2, pred_label.size() - 3)));
			else
				preds.push_back(StringSet::intern(pred_label.substr(1)));
		}
	}

	HeaderNode::HeaderNode(ASTNode *node): BaseNode(llvmParser, LLVM_BLOCKHEADER, "") {
		Deleter deleter(node);
		locate(node);
		label = node->symbol == LLVMTOK_STRING? node->extracted() : node->lexerInfo;
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

	InstructionNode::InstructionNode(const std::string *str):
		BaseNode(llvmParser, LLVM_INSTRUCTION, str) {}

	InstructionNode::InstructionNode():
		BaseNode(llvmParser, LLVM_INSTRUCTION, "") {}

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

	InstructionNode * InstructionNode::fromLLVM(llvm::Instruction *llvm) {
		if (auto *inst = llvm::dyn_cast<llvm::CallInst>(llvm)) {
			return new CallNode(*inst);
		}

		if (auto *inst = llvm::dyn_cast<llvm::ReturnInst>(llvm)) {
			return new RetNode(*inst);
		}

		if (auto *inst = llvm::dyn_cast<llvm::AllocaInst>(llvm)) {
			return new AllocaNode(*inst);
		}

		if (auto *inst = llvm::dyn_cast<llvm::StoreInst>(llvm)) {
			return new StoreNode(*inst);
		}

		llvm::raw_os_ostream os(std::cerr);
		llvm->print(os);
		std::cerr << std::endl;
		throw std::invalid_argument("Unhandled LLVM instruction");
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

	SelectNode::SelectNode(const std::string *result_, std::unordered_set<Fastmath> fastmath_, TypePtr condition_type,
	                       TypePtr first_type, TypePtr second_type, ValuePtr condition_value, ValuePtr first_value,
	                       ValuePtr second_value, int debug_index):
	fastmath(std::move(fastmath_)), conditionType(std::move(condition_type)), firstType(std::move(first_type)),
	secondType(std::move(second_type)), conditionValue(std::move(condition_value)),
	firstValue(std::move(first_value)), secondValue(std::move(second_value)) {
		result = result_;
		debugIndex = debug_index;
	}

	std::string SelectNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m" << getResult() << " \e[2m= \e[0;91mselect\e[0;38;5;202m" << fastmath << " " << *conditionType
		    << " " << *conditionValue << "\e[2m,\e[0m " << *firstType << " " << *firstValue << "\e[2m,\e[0m "
		    << *secondType << " " << *secondValue;
		return out.str();
	}

	InstructionNode * SelectNode::copy() const {
		auto out = std::make_unique<SelectNode>(*this);
		Util::copyPointer(out->conditionType);
		Util::copyPointer(out->conditionValue);
		Util::copyPointer(out->firstType);
		Util::copyPointer(out->firstValue);
		Util::copyPointer(out->secondType);
		Util::copyPointer(out->secondValue);
		return out.release();
	}

// AllocaNode

	AllocaNode::AllocaNode(const llvm::AllocaInst &inst) {
		inalloca = inst.isUsedWithInAlloca();
		const llvm::Value *array_size = inst.getArraySize();
		assert(array_size != nullptr);
		numelementsType = Type::fromLLVM(*array_size->getType());
		numelementsValue = Constant::fromLLVM(*array_size)->value;
		align = static_cast<decltype(align)>(inst.getAlign().value());
		addrspace = static_cast<decltype(addrspace)>(inst.getAddressSpace());
	}

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

	InstructionNode * AllocaNode::copy() const {
		auto out = std::make_unique<AllocaNode>(*this);
		Util::copyPointer(out->numelementsType);
		Util::copyPointer(out->numelementsValue);
		return out.release();
	}

// StoreNode

	StoreNode::StoreNode(const llvm::StoreInst &inst) {
		volatile_ = inst.isVolatile();
		atomic = inst.isAtomic();
		source = Constant::fromLLVM(*inst.getOperand(0));
		destination = Constant::fromLLVM(*inst.getOperand(1));
		align = static_cast<decltype(align)>(inst.getAlign().value());
		ordering = getOrdering(inst.getOrdering());
	}

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
		for (const std::pair<const Ordering, std::string> &pair: ordering_map) {
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}
		}

		volatile_ = bool(volatile__);

		if (syncscope_) {
			syncscope = StringSet::intern(syncscope_->extractName());
		}

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

	InstructionNode * StoreNode::copy() const {
		auto out = std::make_unique<StoreNode>(*this);
		Util::copyPointer(out->source);
		Util::copyPointer(out->destination);
		return out.release();
	}

// LoadNode

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *align_,
	                   ASTNode *bangs) {
		Deleter deleter(result_, type_, constant_, volatile__, align_, bangs);
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

	InstructionNode * LoadNode::copy() const {
		auto out = std::make_unique<LoadNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->constant);
		return out.release();
	}

// IcmpNode

	IcmpNode::IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, cond_, left_, right_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		cond   = cond_inv_map.at(*cond_->lexerInfo);
		left   = Constant::make(left_)->convert();
		right  = Constant::make(right_, left->type)->convert();
	}

	IcmpNode::IcmpNode(const std::string *result_, IcmpCond cond_, ConstantPtr left_, ConstantPtr right_):
		cond(cond_), left(left_->convert()), right(right_->convert()) { result = result_; }

	IcmpNode::IcmpNode(VariablePtr variable_, IcmpCond cond_, ConstantPtr left_, ConstantPtr right_):
		cond(cond_), left(left_->convert()), right(right_->convert()) { variable = variable_; }

	std::string IcmpNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[0;91micmp\e[0m " << cond_map.at(cond) << " " << *left << ", " << *right;
		return out.str();
	}

	std::vector<ValuePtr> IcmpNode::allValues() {
		return {left->value, right->value};
	}

	std::vector<ValuePtr *> IcmpNode::allValuePointers() {
		return {&left->value, &right->value};
	}

	std::vector<ConstantPtr> IcmpNode::allConstants() const {
		return {left, right};
	}

	std::vector<ConstantPtr *> IcmpNode::allConstantPointers() {
		return {&left, &right};
	}

	InstructionNode * IcmpNode::copy() const {
		auto out = std::make_unique<IcmpNode>(*this);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
	}

// BrUncondNode

	BrUncondNode::BrUncondNode(ASTNode *node, ASTNode *unibangs): BrUncondNode(node->lexerInfo) {
		Deleter deleter(node, unibangs);
		handleUnibangs(unibangs);
	}

	std::string BrUncondNode::debugExtra() const {
		return "\e[91mbr\e[0;34m label \e[32m" + *destination + "\e[0m";
	}

	InstructionNode * BrUncondNode::copy() const {
		return new BrUncondNode(*this);
	}

// BrCondNode

	BrCondNode::BrCondNode(ASTNode *constant, ASTNode *if_true, ASTNode *if_false, ASTNode *unibangs) {
		Deleter deleter(unibangs, constant, if_true, if_false);
		handleUnibangs(unibangs);
		condition = Constant::make(constant)->convert();
		if (!condition->type->isInt(1))
			llvmerror("Expected i1 for br condition type");
		ifTrue = if_true->lexerInfo;
		ifFalse = if_false->lexerInfo;
	}

	std::string BrCondNode::debugExtra() const {
		return "\e[91mbr\e[39m " + std::string(*condition) + ", label \e[32m" + *ifTrue + "\e[39m, label "
			"\e[32m" + *ifFalse + "\e[39m";
	}

	InstructionNode * BrCondNode::copy() const {
		auto out = std::make_unique<BrCondNode>(*this);
		Util::copyPointer(out->condition);
		return out.release();
	}

// CallInvokeNode

	CallInvokeNode::CallInvokeNode(const llvm::CallInst &inst) {
		cconv = getCConv(inst.getCallingConv());

		for (const auto &attr_list: inst.getAttributes()) {
			for (const auto &attr: attr_list) {
				const llvm::Attribute::AttrKind kind = attr.getKindAsEnum();
				if (inst.hasRetAttr(kind)) {
					retattrs.insert(getRetAttr(kind));
				}
			}
		}

		for (unsigned i = 0, max = inst.getNumOperands(); i < max; ++i) {
			llvm::Value *operand = inst.getOperand(i);
			if (i + 1 == max) {
				std::string name_string;
				llvm::raw_string_ostream os(name_string);
				operand->printAsOperand(os, false);

				if (name_string.empty()) {
					throw std::runtime_error("Callee operand name is empty");
				}

				if (name_string[0] == '@') {
					name = std::make_shared<GlobalValue>(name_string);
				} else if (name_string[0] == '%') {
					name = std::make_shared<LocalValue>(name_string.substr(1));
				} else {
					throw std::runtime_error("Invalid callee operand name");
				}
			} else if (ConstantPtr constant = Constant::fromLLVM(*operand)) {
				constants.push_back(constant);
			}
		}

		llvm::FunctionType *function_type = inst.getFunctionType();
		returnType = Type::fromLLVM(*function_type->getReturnType());
		argumentEllipsis = function_type->isVarArg();
	}

	CallInvokeNode::CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants, ASTNode *attribute_list, ASTNode *unibangs) {
		Deleter deleter(unibangs, _result, _cconv, _retattrs, _addrspace, return_type, _args, function_name, _constants, attribute_list);
		handleUnibangs(unibangs);

		if (_result) {
			result = StringSet::intern(_result->extractName());
		}

		if (_cconv) {
			cconv = getCConv(*_cconv->lexerInfo);
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
		}

		if (_addrspace) {
			addrspace = _addrspace->at(0)->atoi();
		}

		if (return_type) {
			returnType = getType(return_type);
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
				for (ASTNode *typenode: *typelist) {
					argumentTypes.push_back(getType(typenode));
				}
			}
		}

		if (function_name) {
			name = getValue(function_name);
			if (!std::dynamic_pointer_cast<VariableValue>(name)) {
				throw std::runtime_error("Function name isn't a global or local variable");
			}
		}

		if (_constants) {
			for (ASTNode *child: *_constants) {
				constants.push_back(std::make_shared<Constant>(child));
			}
		}

		if (attribute_list) {
			for (ASTNode *child: *attribute_list) {
				attributeIndices.push_back(child->atoi());
			}
		}
	}

	std::vector<ValuePtr> CallInvokeNode::allValues() {
		std::vector<ValuePtr> out;
		out.reserve(constants.size() + 1);
		for (ConstantPtr constant: constants) {
			out.push_back(constant->value);
		}
		if (std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(name)) {
			out.push_back(local);
		}
		return out;
	}

	std::vector<ValuePtr *> CallInvokeNode::allValuePointers() {
		std::vector<ValuePtr *> out;
		out.reserve(constants.size() + 1);
		for (ConstantPtr &constant: constants) {
			out.push_back(&constant->value);
		}
		if (std::shared_ptr<LocalValue> local = std::dynamic_pointer_cast<LocalValue>(name)) {
			out.push_back(&name);
		}
		return out;
	}

	std::vector<ConstantPtr *> CallInvokeNode::allConstantPointers() {
		std::vector<ConstantPtr *> out;
		for (ConstantPtr &ptr: constants) {
			out.push_back(&ptr);
		}
		return out;
	}

	CallInvokeNode * CallInvokeNode::copyTo(CallInvokeNode &other) const {
		other.constants.clear();
		for (const auto &constant: constants) {
			if (constant) {
				other.constants.push_back(constant->copy());
			} else {
				other.constants.push_back(nullptr);
			}
		}
		other.argumentTypes.clear();
		for (const auto &argument_type: argumentTypes) {
			if (argument_type) {
				other.argumentTypes.push_back(argument_type->copy());
			} else {
				other.argumentTypes.push_back(nullptr);
			}
		}
		return &other;
	}

// CallNode

	CallNode::CallNode(const llvm::CallInst &inst):
		CallInvokeNode(inst) {
			tail = getTailCallKind(inst.getTailCallKind());
			fastmath = getFastmath(inst.getFastMathFlags());
		}

	CallNode::CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                   ASTNode *return_type, ASTNode *_args, ASTNode *constant, ASTNode *_constants, ASTNode *attribute_list, ASTNode *unibangs):
		CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, constant, _constants, attribute_list, unibangs) {
			Deleter deleter(_tail);
			if (_tail && _tail->lexerInfo) {
				tail = getTailCallKind(*_tail->lexerInfo);
			}
			getFastmath(fastmath, fastmath_flags);
		}

	std::string CallNode::debugExtra() const {
		std::stringstream out;
		if (result) {
			out << getResult() << "\e[2m = ";
		}
		print(out, "\e[22;34m", tail_call_kind_map.at(tail), " ");
		out << "\e[22;91mcall\e[39m" << fastmath;
		if (!fastmath.empty()) {
			out << "\e[2m .\e[22m";
		}
		print(out, " \e[34m", cconv_map.at(cconv), "\e[39;2m .\e[22m");
		for (RetAttr attr: retattrs) {
			out << " \e[34m" << retattr_map.at(attr) << "\e[39m";
		}
		print(out, " \e[34mdereferenceable\e[39;2m(\e[22m", dereferenceable, "\e[2m)\e[22m");
		if (!retattrs.empty() || dereferenceable != -1) {
			out << " \e[2m.\e[22m";
		}
		print(out, " \e[34maddrspace\e[39;2m(\e[22m", addrspace, "\e[2m)\e[22m");
		out << " " << *returnType;
		if (argumentsExplicit) {
			out << " \e[1;2m(\e[22m";
			for (auto begin = argumentTypes.cbegin(), iter = begin, end = argumentTypes.cend(); iter != end; ++iter) {
				if (iter != begin) {
					out << "\e[2m, \e[22m";
				}
				out << **iter;
			}
			if (argumentEllipsis) {
				out << "\e[2m" << (argumentTypes.empty()? "" : ", ") << "...\e[22m";
			}
			out << "\e[1;2m)\e[22m";
		}
		out << " " << *name << "\e[2m(\e[22m";
		for (auto begin = constants.begin(), iter = begin, end = constants.end(); iter != end; ++iter) {
			if (iter != begin) {
				out << "\e[2m,\e[22m ";
			}
			out << **iter;
		}
		out << "\e[2m)\e[22m";
		return out.str();
	}

	InstructionNode * CallNode::copy() const {
		auto out = std::make_unique<CallNode>(*this);
		copyTo(*out);
		return out.release();
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

	InstructionNode * AsmNode::copy() const {
		auto out = std::make_unique<AsmNode>(*this);
		copyTo(*out);
		return out.release();
	}

// InvokeNode

	InvokeNode::InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                       ASTNode *return_type, ASTNode *_args, ASTNode *constant, ASTNode *_constants,
	                       ASTNode *attribute_list, ASTNode *normal_label, ASTNode *exception_label, ASTNode *unibangs):
	                       CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, constant,
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
		print(out, " \e[34m", cconv_map.at(cconv), "\e[0;2m .\e[0m");
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

	InstructionNode * InvokeNode::copy() const {
		auto out = std::make_unique<InvokeNode>(*this);
		return copyTo(*out);
		return out.release();
	}

// GetelementptrNode

	GetelementptrNode::GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *constant_,
	                                     ASTNode *indices_, ASTNode *unibangs) {
		Deleter deleter(unibangs, _inbounds, pvar, type_, constant_, indices_);
		handleUnibangs(unibangs);
		result = StringSet::intern(pvar->extractName());
		inbounds = bool(_inbounds);
		type = getType(type_);
		constant = Constant::make(constant_)->convert();
		pointerType = constant->type;

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

	InstructionNode * GetelementptrNode::copy() const {
		auto out = std::make_unique<GetelementptrNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->pointerType);
		Util::copyPointer(out->cachedConstantValue);
		return out.release();
	}

// RetNode

	RetNode::RetNode(const llvm::ReturnInst &inst) {
		if (llvm::Value *return_value = inst.getReturnValue()) {
			type = Type::fromLLVM(*return_value->getType());
			value = Constant::fromLLVM(*return_value)->value;
		} else {
			type = VoidType::make();
			value = VoidValue::make();
		}
	}

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

	InstructionNode * RetNode::copy() const {
		auto out = std::make_unique<RetNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->value);
		return out.release();
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

	LandingpadNode::Clause * LandingpadNode::Clause::copy() const {
		auto out = std::make_unique<LandingpadNode::Clause>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->value);
		return out.release();
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

	InstructionNode * LandingpadNode::copy() const {
		auto out = std::make_unique<LandingpadNode>(*this);
		Util::copyPointer(out->type);
		out->clauses.clear();
		for (const auto &clause: clauses)
			out->clauses.emplace_back(clause? clause->copy() : nullptr);
		return out.release();
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

	InstructionNode * ConversionNode::copy() const {
		auto out = std::make_unique<ConversionNode>(*this);
		Util::copyPointer(out->from);
		Util::copyPointer(out->to);
		Util::copyPointer(out->value);
		return out.release();
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

	InstructionNode * BasicMathNode::copy() const {
		auto out = std::make_unique<BasicMathNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
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

	InstructionNode * PhiNode::copy() const {
		auto out = std::make_unique<PhiNode>(*this);
		Util::copyPointer(out->type);
		out->pairs.clear();
		for (const auto &[value, string]: pairs)
			out->pairs.emplace_back(value? value->copy() : nullptr, string);
		return out.release();
	}

// SimpleNode

	SimpleNode::SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, type_, left_, right_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		locate(result_);
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

	InstructionNode * DivNode::copy() const {
		auto out = std::make_unique<DivNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
	}

// RemNode

	RemNode::RemNode(ASTNode *result_, ASTNode *rem, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		Deleter deleter(exact_, rem);
		exact = bool(exact_);
		remType = *rem->lexerInfo == "srem"? RemType::Srem : RemType::Urem;
	}

	InstructionNode * RemNode::copy() const {
		auto out = std::make_unique<RemNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
	}

// LogicNode

	LogicNode::LogicNode(ASTNode *result_, ASTNode *logic_type, ASTNode *left_, ASTNode *right_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, logic_type, left_, right_);
		handleUnibangs(unibangs);
		result    = result_->extracted();
		logicType = logic_inv_map.at(*logic_type->lexerInfo);
		left      = Constant::make(left_)->convert();
		right     = Constant::make(right_, left->type)->convert();
	}

	LogicNode::LogicNode(const std::string *result_, LogicType logic_type, ConstantPtr left_, ConstantPtr right_):
		logicType(logic_type), left(left_->convert()), right(right_->convert()) { result = result_; }

	LogicNode::LogicNode(VariablePtr variable_, LogicType logic_type, ConstantPtr left_, ConstantPtr right_):
		logicType(logic_type), left(left_->convert()), right(right_->convert()) { variable = variable_; }

	std::string LogicNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[22;91m" << logic_map.at(logicType) << " " << *left << ", " << *right;
		return out.str();
	}

	std::vector<ValuePtr> LogicNode::allValues() {
		return {left->value, right->value};
	}

	std::vector<ValuePtr *> LogicNode::allValuePointers() {
		return {&left->value, &right->value};
	}

	std::vector<ConstantPtr> LogicNode::allConstants() const {
		return {left, right};
	}

	std::vector<ConstantPtr *> LogicNode::allConstantPointers() {
		return {&left, &right};
	}

	InstructionNode * LogicNode::copy() const {
		auto out = std::make_unique<LogicNode>(*this);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
	}

// ShrNode

	ShrNode::ShrNode(ASTNode *result_, ASTNode *shr, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
	                 ASTNode *unibangs): SimpleNode(result_, type_, left_, right_, unibangs) {
		Deleter deleter(exact_, shr);
		exact = bool(exact_);
		shrType = *shr->lexerInfo == "lshr"? ShrType::Lshr : ShrType::Ashr;
	}

	InstructionNode * ShrNode::copy() const {
		auto out = std::make_unique<ShrNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
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

	InstructionNode * FMathNode::copy() const {
		auto out = std::make_unique<FMathNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->left);
		Util::copyPointer(out->right);
		return out.release();
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

	InstructionNode * SwitchNode::copy() const {
		auto out = std::make_unique<SwitchNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->value);
		out->table.clear();
		for (const auto &[t, v, s]: table)
			out->table.emplace_back(t? t->copy() : nullptr, v? v->copy() : nullptr, s);
		return out.release();
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

	InstructionNode * ExtractValueNode::copy() const {
		auto out = std::make_unique<ExtractValueNode>(*this);
		if (out->aggregateType)
			out->aggregateType = std::dynamic_pointer_cast<AggregateType>(out->aggregateType);
		Util::copyPointer(out->aggregateValue);
		return out.release();
	}

// InsertValueNode

	InsertValueNode::InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value,
	                                 ASTNode *type_, ASTNode *value_, ASTNode *decimals_, ASTNode *unibangs) {
		Deleter deleter(unibangs, result_, aggregate_type, aggregate_value, type_, value_, decimals_);
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

	InstructionNode * InsertValueNode::copy() const {
		auto out = std::make_unique<InsertValueNode>(*this);
		Util::copyPointer(out->aggregateType);
		Util::copyPointer(out->type);
		Util::copyPointer(out->aggregateValue);
		Util::copyPointer(out->value);
		return out.release();
	}

// ResumeNode

	ResumeNode::ResumeNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs) {
		Deleter deleter(unibangs, type_, value_);
		handleUnibangs(unibangs);
		type = getType(type_);
		value = getValue(value_);
	}

	std::string ResumeNode::debugExtra() const {
		return "\e[91mresume\e[39m " + std::string(*type) + " " + std::string(*value);
	}

	InstructionNode * ResumeNode::copy() const {
		auto out = std::make_unique<ResumeNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->value);
		return out.release();
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

	InstructionNode * FreezeNode::copy() const {
		auto out = std::make_unique<FreezeNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->value);
		return out.release();
	}

// DbgIntrinsicNode

	DbgIntrinsicNode::DbgIntrinsicNode(ASTNode *type_, ASTNode *constant_, ASTNode *first_metadata,
	                                   ASTNode *second_metadata, ASTNode *unibangs) {
		Deleter deleter(unibangs, constant_, type_);
		handleUnibangs(unibangs);
		type = type_->symbol == LLVMTOK_DBG_VALUE? Type::Value : Type::Declare;
		constant = Constant::make(constant_);
		adopt({firstMetadata = first_metadata, secondMetadata = second_metadata});
	}

	std::string DbgIntrinsicNode::debugExtra() const {
		if (type == Type::Invalid)
			return "\e[101minvalid @llvm.dbg.* intrinsic\e[49m";
		std::stringstream out;
		out << "\e[91mcall \e[34mvoid @llvm.dbg." << (type == Type::Value? "value" : "declare") << "\e[39;2m(\e[22;34m";
		out << "metadata\e[39m " << std::string(*constant) << "\e[2m,\e[22;34m metadata\e[39m ";
		out << firstMetadata->recursiveStringify() << "\e[2m,\e[22;34m metadata\e[39m ";
		out << secondMetadata->recursiveStringify() << "\e[2m)\e[22m";
		return out.str();
	}

	InstructionNode * DbgIntrinsicNode::copy() const {
		auto out = std::make_unique<DbgIntrinsicNode>(*this);
		Util::copyPointer(out->constant);
		Util::copyPointer(out->firstMetadata);
		Util::copyPointer(out->secondMetadata);
		return out.release();
	}

// AtomicrmwNode

	std::unordered_map<std::string, AtomicrmwNode::Op> AtomicrmwNode::opMap {
		{"xchg", Op::Xchg}, {"add",  Op::Add},  {"sub",  Op::Sub},  {"and",  Op::And},  {"nand", Op::Nand},
		{"or",   Op::Or},   {"xor",  Op::Xor},  {"max",  Op::Max},  {"min",  Op::Min},  {"umax", Op::Umax},
		{"umin", Op::Umin}, {"fadd", Op::Fadd}, {"fsub", Op::Fsub}, {"fmax", Op::Fmax}, {"fmin", Op::Fmin},
	};

	AtomicrmwNode::AtomicrmwNode(ASTNode *result_, ASTNode *_volatile_, ASTNode *op_, ASTNode *pointer_type,
	                             ASTNode *pointer_, ASTNode *type_, ASTNode *value_, ASTNode *syncscope_,
	                             ASTNode *ordering_, ASTNode *align_, ASTNode *unibangs):
	opString(op_->lexerInfo) {
		Deleter deleter(unibangs, _volatile_, op_, pointer_type, pointer_, type_, value_, syncscope_, ordering_,
		                align_);
		handleUnibangs(unibangs);
		result = result_->extracted();
		op = opMap.at(*opString);
		pointerType = getType(pointer_type);
		pointer = getValue(pointer_);
		type = getType(type_);
		value = getValue(value_);
		if (syncscope_ != nullptr)
			syncscope = syncscope_->extracted();
		volatile_ = bool(_volatile_);
		if (align_ != nullptr)
			align = align_->atoi();
		for (const std::pair<const Ordering, std::string> &pair: ordering_map)
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}
	}

	std::string AtomicrmwNode::debugExtra() const {
		std::stringstream out;
		out << getResult() << "\e[2m = \e[22;91matomicrmw\e[39m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[39m";
		out << " \e[91m" << *opString << "\e[39m " << *pointerType << ' ' << *pointer << "\e[2m,\e[22m " << *type << ' '
		    << *value;
		if (syncscope != nullptr)
			out << " \e[34msyncscope\e[39;2m(\e[22m\"" << *syncscope << "\"\e[2m)\e[22m";
		if (ordering != Ordering::None)
			out << " \e[38;5;202m" << ordering_map.at(ordering) << "\e[39m";
		if (align != -1)
			out << "\e[2m,\e[22;34m align \e[39m" << align;
		return out.str();
	}

	InstructionNode * AtomicrmwNode::copy() const {
		auto out = std::make_unique<AtomicrmwNode>(*this);
		Util::copyPointer(out->type);
		Util::copyPointer(out->pointerType);
		Util::copyPointer(out->pointer);
		Util::copyPointer(out->value);
		return out.release();
	}

// Miscellaneous

	ASTNode * ignoreConversion(ASTNode *node) {
		if (*node->lexerInfo != "bitcast")
			throw std::invalid_argument("Unexpected conversion expr in ignoreConversion: " + *node->lexerInfo);
		return node->at(0)->at(1);
	}
}
