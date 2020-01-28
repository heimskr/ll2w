#include <iostream>
#include <sstream>

#include "Nodes.h"
#include "StringSet.h"
#include "Util.h"

namespace LL2W {

// MetadataDef

	MetadataDef::MetadataDef(ASTNode *dotident_node, ASTNode *distinct_node, ASTNode *list):
		ASTNode(TOK_METADATA, StringSet::intern(dotident_node->concatenate().c_str())) {
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

	HeaderNode::HeaderNode(ASTNode *node): ASTNode(BLOCKHEADER, "") {
		locate(node);
		label = node->at(0)->atoi();
		preds.reserve(node->at(2)->size());
		for (ASTNode *pred: *node->at(2))
			preds.push_back(pred->atoi(1));
		delete node;
	}

	std::string HeaderNode::debugExtra() const {
		std::stringstream out;
		out << "\e[2;4m<label>:" << label << "; preds =";
		for (int pred: preds)
			out << " %" << pred;
		out << "\e[0m";
		return out.str();
	}

// SelectNode

	SelectNode::SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type,
	                       ASTNode *condition_value, ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2) {
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

	SelectNode::~SelectNode() {
		delete conditionType;
		delete conditionValue;
		delete firstType;
		delete firstValue;
		delete secondType;
		delete secondValue;
	}

	std::string SelectNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << " \e[2m= \e[0;91mselect\e[0;38;5;202m" << fastmath << " "
		    << std::string(*conditionType) << " " << std::string(*conditionValue) << "\e[2m,\e[0m "
		    << std::string(*firstType) << " " << std::string(*firstValue) << "\e[2m,\e[0m " << std::string(*secondType)
		    << " " << std::string(*secondValue);
		return out.str();
	}

// AllocaNode

	AllocaNode::AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
	                       ASTNode *addrspace_) {
		result = result_->extracted();
		delete result_;

		if (inalloca_) {
			inalloca = true;
			delete inalloca_;
		}

		type = getType(type_);
		delete type_;

		// numelements_ is expected to be a TOK_COMMA node with a type_any child and a TOK_DECIMAL child.
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

	AllocaNode::~AllocaNode() {
		delete type;
		if (numelementsType) delete numelementsType;
		if (numelementsValue) delete numelementsValue;
	}

	std::string AllocaNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91malloca\e[0m";
		if (inalloca)
			out << " \e[38;5;202minalloca\e[0m";
		out << " " << std::string(*type);
		if (numelementsType)
			out << "\e[2m,\e[0m " << std::string(*numelementsType) << " " << std::string(*numelementsValue);
		print(out, "\e[2m,\e[0;34m align\e[0m ", align);
		print(out, "\e[2m,\e[0;34m addrspace\e[0m(", addrspace, ")");
		return out.str();
	}

// StoreNode

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *constant_, ASTNode *align_,
	                     ASTNode *nontemporal_, ASTNode *invariant_group) {
		atomic = false;
		type = getType(type_);
		value = getValue(value_);
		constant = new Constant(constant_);

		delete type_;
		delete value_;
		delete constant_;

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		if (align_) {
			align = align_->atoi();
			delete align_;
		}

		if (nontemporal_) { // TOK_INTBANG "!42"
			nontemporalIndex = nontemporal_->atoi(1);
			delete nontemporal_;
		}

		if (invariant_group) { // Same as above
			invariantGroupIndex = invariant_group->atoi(1);
			delete invariant_group;
		}
	}

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *constant_, ASTNode *syncscope_,
	                     ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group) {
		atomic = true;
		type = getType(type_);
		value = getValue(value_);
		constant = new Constant(constant_);
		align = align_->atoi();
		for (const std::pair<Ordering, std::string> &pair: ordering_map) {
			if (*ordering_->lexerInfo == pair.second) {
				ordering = pair.first;
				break;
			}
		}

		delete type_;
		delete value_;
		delete constant_;
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

		if (invariant_group) {
			invariantGroupIndex = invariant_group->atoi(1);
			delete invariant_group;
		}
	}

	StoreNode::~StoreNode() {
		delete type;
		delete value;
		delete constant;
	}

	std::string StoreNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91mstore\e[0m";
		if (atomic)
			out << " \e[38;5;202matomic\e[0m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[0m";
		out << "\e[0m " << std::string(*type) << " " << std::string(*value) << "\e[2m,\e[0m " << std::string(*constant);
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

// LoadNode

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *align_,
	                   ASTNode *nontemporal_, ASTNode *invariant_load, ASTNode *invariant_group, ASTNode *nonnull_,
	                   ASTNode *dereferenceable_, ASTNode *dereferenceable_or_null, ASTNode *bang_align) {
		atomic = false;
		result = result_->extracted();
		type = getType(type_);
		constant = new Constant(constant_);

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

		if (nontemporal_) {
			nontemporalIndex = nontemporal_->atoi(1);
			delete nontemporal_;
		}

		if (invariant_load) {
			invariantLoadIndex = invariant_load->atoi(1);
			delete invariant_load;
		}

		if (invariant_group) {
			invariantGroupIndex = invariant_group->atoi(1);
			delete invariant_group;
		}

		if (nonnull_) {
			nonnullIndex = nonnull_->atoi(1);
			delete nonnull_;
		}

		if (dereferenceable_) {
			dereferenceable = dereferenceable_->lexerInfo;
			delete dereferenceable_;
		}

		if (dereferenceable_or_null) {
			dereferenceableOrNull = dereferenceable_or_null->lexerInfo;
			delete dereferenceable_or_null;
		}

		if (bang_align) {
			bangAlign = bang_align->lexerInfo;
			delete bang_align;
		}
	}

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *syncscope_,
	                   ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group) {
		atomic = true;
		result = result_->extracted();
		type = getType(type_);
		constant = new Constant(constant_);
		align = align_->atoi();
		for (const std::pair<Ordering, std::string> &pair: ordering_map) {
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

		if (invariant_group) {
			invariantGroupIndex = invariant_group->atoi(1);
			delete invariant_group;
		}
	}

	LoadNode::~LoadNode() {
		delete type;
		delete constant;
	}

	std::string LoadNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91mload\e[0m";
		if (atomic)
			out << " \e[38;5;202matomic\e[0m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[0m";
		out << "\e[0m " << std::string(*type) << "\e[2m,\e[0m " << std::string(*constant);
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

	IcmpNode::IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op1, ASTNode *op2) {
		result = result_->extracted();

		for (const std::pair<IcmpCond, std::string> &pair: cond_map) {
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

	IcmpNode::~IcmpNode() {
		delete type;
		delete value1;
		delete value2;
	}

	std::string IcmpNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91micmp\e[0m " << cond_map.at(cond) << " " << std::string(*type)
		    << " " << std::string(*value1) << ", " << std::string(*value2);
		return out.str();
	}

// BrUncondNode

	std::string BrUncondNode::debugExtra() const {
		return "\e[91mbr\e[0;34m label \e[32m" + *destination + "\e[0m";
	}

// BrCondNode

	BrCondNode::BrCondNode(ASTNode *type, ASTNode *condition_, ASTNode *if_true, ASTNode *if_false) {
		if (*type->lexerInfo != "i1")
			yyerror("Expected i1 for br condition type");
		condition = getValue(condition_);
		ifTrue = if_true->lexerInfo;
		ifFalse = if_false->lexerInfo;

		delete condition_;
		delete if_true;
		delete if_false;
	}

	BrCondNode::~BrCondNode() {
		delete condition;
	}

	std::string BrCondNode::debugExtra() const {
		return "\e[91mbr \e[33mi1\e[39m " + std::string(*condition) + ", label \e[32m" + *ifTrue + "\e[39m, label "
			"\e[32m" + *ifFalse + "\e[39m";
	}

// CallInvokeNode

	CallInvokeNode::CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
	                               ASTNode *attribute_list) {
		if (_result) {
			result = StringSet::intern(_result->extractName());
			delete _result;
		}

		if (_cconv) {
			cconv = _cconv->lexerInfo;
			delete _cconv;
		}

		for (ASTNode *child: *_retattrs) {
			const std::string &raname = *child->lexerInfo;
			if (raname == "dereferenceable") {
				dereferenceable = child->at(0)->atoi();
			} else {
				for (const std::pair<RetAttr, std::string> &pair: retattr_map) {
					if (raname == pair.second) {
						retattrs.insert(pair.first);
						break;
					}
				}
			}
		}
		delete _retattrs;

		if (_addrspace) {
			addrspace = _addrspace->at(0)->atoi();
			delete _addrspace;
		}

		returnType = getType(return_type);
		delete return_type;

		if (_args) {
			argumentsExplicit = true;
			ASTNode *typelist = nullptr;
			if (_args->size() == 2) { // Both a typelist and an ellipsis are specified.
				argumentEllipsis = true;
				typelist = _args->at(0);
			} else if (_args->size() == 1) { // Either a typelist or an ellipsis is specified.
				if (_args->at(0)->symbol == TOK_ELLIPSIS) {
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

		name = dynamic_cast<VariableValue *>(getValue(function_name));
		delete function_name;
		if (!name) {
			if (_constants)
				delete _constants;
			delete attribute_list;
			throw std::runtime_error("Function name isn't a global or local variable");
		}

		if (_constants) {
			for (ASTNode *child: *_constants)
				constants.push_back(new Constant(child));
			delete _constants;
		}

		for (ASTNode *child: *attribute_list)
			attributeIndices.push_back(child->atoi());
		delete attribute_list;
	}

	CallInvokeNode::~CallInvokeNode() {
		delete returnType;
		delete name;
		for (Constant *constant: constants)
			delete constant;
		for (Type *type: argumentTypes)
			delete type;
	}

// CallNode

	CallNode::CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv,
	                   ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args,
	                   ASTNode *function_name, ASTNode *_constants, ASTNode *attribute_list):
	                   CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, function_name,
	                                  _constants, attribute_list) {
		if (_tail) {
			tail = _tail->lexerInfo;
			delete _tail;
		}

		getFastmath(fastmath, fastmath_flags);
	}

	std::string CallNode::debugExtra() const {
		std::stringstream out;
		print(out, "\e[32m%", result, "\e[0;2m = ");
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
		out << " " << std::string(*returnType);
		if (argumentsExplicit) {
			out << " \e[1;2m(\e[0m";
			for (auto begin = argumentTypes.cbegin(), iter = begin, end = argumentTypes.cend(); iter != end; ++iter) {
				if (iter != begin)
					out << "\e[2m, \e[0m";
				out << std::string(**iter);
			}
			if (argumentEllipsis)
				out << "\e[2m" << (argumentTypes.empty()? "" : ", ") << "...\e[0m";
			out << "\e[1;2m)\e[0m";
		}
		out << " " << std::string(*name) << "\e[2m(\e[0m";
		for (auto begin = constants.begin(), iter = begin, end = constants.end(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(**iter);
		}
		out << "\e[2m)\e[0m";
		return out.str();
	}

// InvokeNode

	InvokeNode::InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
	                       ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
	                       ASTNode *attribute_list, ASTNode *normal_label, ASTNode *exception_label):
	                       CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, function_name,
	                                      _constants, attribute_list) {
		normalLabel = StringSet::intern(normal_label->extractName());
		delete normal_label;

		exceptionLabel = StringSet::intern(exception_label->extractName());
		delete exception_label;
	}

	std::string InvokeNode::debugExtra() const {
		std::stringstream out;
		if (result)
			out << "\e[32m%" << *result << "\e[0;2m = ";
		out << "\e[0;91minvoke\e[0m";
		if (cconv)
			out << " \e[34m" << *cconv << "\e[0;2m .\e[0m";
		for (RetAttr attr: retattrs)
			out << " \e[34m" << retattr_map.at(attr) << "\e[0m";
		if (dereferenceable != -1)
			out << " \e[34mdereferenceable\e[0;2m(\e[0m" << dereferenceable << "\e[2m)\e[0m";
		if (!retattrs.empty() || dereferenceable != -1)
			out << " \e[0;2m.\e[0m";
		if (addrspace != -1)
			out << " \e[34maddrspace\e[0;2m(\e[0m" << addrspace << "\e[2m)\e[0m";
		out << " " << std::string(*returnType);
		if (argumentsExplicit) {
			out << " \e[1;2m(\e[0m";
			for (auto begin = argumentTypes.cbegin(), iter = begin, end = argumentTypes.cend(); iter != end; ++iter) {
				if (iter != begin)
					out << "\e[2m, \e[0m";
				out << std::string(**iter);
			}
			if (argumentEllipsis)
				out << "\e[2m" << (argumentTypes.empty()? "" : ", ") << "...\e[0m";
			out << "\e[1;2m)\e[0m";
		}
		out << " " << std::string(*name) << "\e[2m(\e[0m";
		for (auto begin = constants.begin(), iter = begin, end = constants.end(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(**iter);
		}
		out << "\e[2m)\e[0;91m to \e[34mlabel %" << *normalLabel << " \e[91munwind\e[34m label %" << *exceptionLabel
		    << "\e[0m";
		return out.str();
	}

// GetelementptrNode

	GetelementptrNode::GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *ptr_type,
	                                     ASTNode *ptrval, ASTNode *indices_) {
		result = StringSet::intern(pvar->extractName());
		if (_inbounds) {
			inbounds = true;
			delete _inbounds;
		}
		type = getType(type_);
		ptrType = getType(ptr_type);
		ptrValue = StringSet::intern(ptrval->extractName());
		for (ASTNode *comma: *indices_) {
			indices.push_back({
				comma->at(0)->atoi(1),
				comma->at(1)->atoi(),
				comma->size() == 3});
		}

		delete pvar;
		delete type_;
		delete ptr_type;
		delete ptrval;
		delete indices_;
	}

	GetelementptrNode::~GetelementptrNode() {
		delete type;
		delete ptrType;
	}

	std::string GetelementptrNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << " \e[0;2m= \e[0;91mgetelementptr\e[0m ";
		if (inbounds)
			out << "\e[34minbounds\e[0m ";
		out << std::string(*type) << "\e[2m,\e[0m " << std::string(*ptrType) << " \e[32m%" << *ptrValue << "\e[0m";
		for (const std::tuple<int, int, bool> &index: indices) {
			out << "\e[2m,\e[0m ";
			if (std::get<2>(index))
				out << "\e[34minrange\e[0m ";
			out << "\e[33mi" << std::get<0>(index) << "\e[0m " << std::get<1>(index);
		}
		return out.str();
	}

// RetNode

	RetNode::RetNode(): type(new VoidType()), value(new VoidValue()) {}

	RetNode::RetNode(ASTNode *type_, ASTNode *value_) {
		type = getType(type_);
		value = getValue(value_);

		delete type_;
		delete value_;
	}

	RetNode::~RetNode() {
		delete type;
		delete value;
	}

	std::string RetNode::debugExtra() const {
		const std::string type_str = std::string(*type);
		return "\e[91mret\e[0m " + (type_str != "void"? type_str + " " + std::string(*value) : type_str);
	}

// LandingpadNode

	LandingpadNode::Clause::Clause(ASTNode *node) {
		clauseType = node->symbol == TOK_CATCH? ClauseType::Catch : ClauseType::Filter;
		if (node->at(0)->symbol == ARRAY_VALUE) {
			type = getType(node->at(0)->at(0));
			value = getValue(node->at(0)->at(1));
		} else {
			type = getType(node->at(0));
			value = getValue(node->at(1));
		}
	}

	LandingpadNode::Clause::~Clause() {
		delete type;
		delete value;
	}

	LandingpadNode::Clause::operator std::string() const {
		return (clauseType == ClauseType::Catch? "catch" : "filter") + (type? " " + std::string(*type) : "") + " " +
			std::string(*value);
	}

	LandingpadNode::LandingpadNode(ASTNode *result_, ASTNode *type_, ASTNode *clauses_, bool cleanup_) {
		result = result_->extracted();
		type = getType(type_);
		for (ASTNode *clause: *clauses_) {
			clauses.push_back(new Clause(clause));
		}
		cleanup = cleanup_;

		delete result_;
		delete type_;
		delete clauses_;
	}

	LandingpadNode::~LandingpadNode() {
		delete type;
		for (Clause *clause: clauses)
			delete clause;
	}

	std::string LandingpadNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91mlandingpad\e[0m " << std::string(*type);
		if (cleanup)
			out << " cleanup";
		for (const Clause *clause: clauses)
			out << " " << std::string(*clause);
		return out.str();
	}

// ConversionNode

	ConversionNode::ConversionNode(ASTNode *result_, ASTNode *conv_op, ASTNode *from_, ASTNode *value_, ASTNode *to_) {
		result = result_->extracted();
		from = getType(from_);
		value = getValue(value_);
		to = getType(to_);
		for (const std::pair<Conversion, std::string> &pair: conversion_map) {
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

	ConversionNode::~ConversionNode() {
		delete from;
		delete to;
		delete value;
	}

	std::string ConversionNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91m" << conversion_map.at(conversionType) << "\e[0m "
		    << std::string(*from) << " " << std::string(*value) << " \e[91mto\e[0m " << std::string(*to);
		return out.str();
	}

// BasicMathNode

	BasicMathNode::BasicMathNode(ASTNode *result_, ASTNode *oper_, bool nuw_, bool nsw_, ASTNode *type_,
	                             ASTNode *left_, ASTNode *right_) {
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

	BasicMathNode::~BasicMathNode() {
		delete type;
		delete left;
		delete right;
	}

	std::string BasicMathNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91m" << *oper << " " << std::string(*type) << " "
		    << std::string(*left) << "\e[2m,\e[0m " << std::string(*right);
		return out.str();
	}

// PhiNode

	PhiNode::PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_) {
		result = result_->extracted();
		type = getType(type_);
		getFastmath(fastmath, fastmath_);
		for (ASTNode *node: *pairs_)
			pairs.push_back({getValue(node->at(0)), node->at(1)->extracted()});

		delete result_;
		delete type_;
		delete pairs_;
	}

	PhiNode::~PhiNode() {
		delete type;
		for (const std::pair<Value *, const std::string *> &pair: pairs)
			delete pair.first;
	}

	std::string PhiNode::debugExtra() const {
		return "??";
	}

// SimpleNode

	SimpleNode::SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_) {
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

	SimpleNode::~SimpleNode() {
		delete type;
		delete left;
		delete right;
	}

	std::string SimpleNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91m" << typeName() << "\e[0m "
		    << std::string(*type) << " " << std::string(*left) << "\e[2m,\e[0m " << std::string(*right);
		return out.str();
	}

// DivNode

	DivNode::DivNode(ASTNode *result_, ASTNode *div, ASTNode *type_, ASTNode *left_, ASTNode *right_):
		SimpleNode(result_, type_, left_, right_) {
		divType = *div->lexerInfo == "sdiv"? DivType::Sdiv : DivType::Udiv;
	}

// RemNode

	RemNode::RemNode(ASTNode *result_, ASTNode *rem, ASTNode *type_, ASTNode *left_, ASTNode *right_):
		SimpleNode(result_, type_, left_, right_) {
		remType = *rem->lexerInfo == "srem"? RemType::Srem : RemType::Urem;
	}

// LogicNode

	LogicNode::LogicNode(ASTNode *result_, ASTNode *logic, ASTNode *type_, ASTNode *left_, ASTNode *right_):
		SimpleNode(result_, type_, left_, right_) {
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

	ShrNode::ShrNode(ASTNode *result_, ASTNode *shr, ASTNode *type_, ASTNode *left_, ASTNode *right_):
		SimpleNode(result_, type_, left_, right_) {
		shrType = *shr->lexerInfo == "lshr"? ShrType::Lshr : ShrType::Ashr;
	}

// FMathNode

	FMathNode::FMathNode(ASTNode *result_, ASTNode *fmath, ASTNode *flags, ASTNode *type_, ASTNode *left_,
	                     ASTNode *right_): SimpleNode(result_, type_, left_, right_) {
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
		out << "\e[32m%" << *result << "\e[2m = \e[0;91m" << typeName() << fastmath << "\e[0m " << std::string(*type)
		    << " " << std::string(*left) << "\e[2m,\e[0m " << std::string(*right);
		return out.str();
	}

// SwitchNode

	SwitchNode::SwitchNode(ASTNode *type_, ASTNode *value_, ASTNode *label_, ASTNode *table_) {
		type = getType(type_);
		value = getValue(value_);
		label = label_->extracted();
		table.reserve(table_->size());
		for (ASTNode *comma: *table_)
			table.push_back({getType(comma->at(0)), getValue(comma->at(1)), comma->at(2)->extracted()});
	}

	SwitchNode::~SwitchNode() {
		delete type;
		delete value;
		for (std::tuple<Type *, Value *, const std::string *> &tuple: table) {
			delete std::get<0>(tuple);
			delete std::get<1>(tuple);
		}
	}

	std::string SwitchNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91mswitch\e[0m " << *type << " " << *value << "\e[2m,\e[0;34m label %" << *label << " \e[0;2m[\e[0m";
		for (auto begin = table.cbegin(), iter = begin, end = table.cend(); iter != end; ++iter) {
			if (iter != begin)
				out << " ";
			const std::tuple<Type *, Value *, const std::string *> &tuple = *iter;
			out << *std::get<0>(tuple) << " " << *std::get<1>(tuple) << ", \e[34mlabel %" << *std::get<2>(tuple)
			    << "\e[0m";
		}
		out << "\e[2m]\e[0m";
		return out.str();
	}

// ExtractValueNode

	ExtractValueNode::ExtractValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value,
	                                   ASTNode *decimals_) {
		result = result_->extracted();
		aggregateType = getType(aggregate_type);
		aggregateValue = getValue(aggregate_value);
		for (ASTNode *decimal: *decimals_)
			decimals.push_back(decimal->atoi());

		delete result_;
		delete aggregate_type;
		delete aggregate_value;
		delete decimals_;
	}

	ExtractValueNode::~ExtractValueNode() {
		delete aggregateType;
		delete aggregateValue;
	}

	std::string ExtractValueNode::debugExtra() const {
		std::stringstream out;
		out << "\e[34m%" << *result << " \e[0;2m= \e[0;91mextractvalue\e[0m " << std::string(*aggregateType) << " "
		    << std::string(*aggregateValue);
		for (int decimal: decimals)
			out << "\e[2m,\e[0m " << decimal;
		return out.str();
	}

// InsertValueNode

	InsertValueNode::InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value,
	                                 ASTNode *type_, ASTNode *value_, ASTNode *decimals_) {
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

	InsertValueNode::~InsertValueNode() {
		delete aggregateType;
		delete aggregateValue;
		delete type;
		delete value;
	}

	std::string InsertValueNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91minsertvalue\e[0m " << std::string(*aggregateType) << " " << std::string(*aggregateValue)
		    << "\e[2m,\e[0m " << std::string(*type) << " " << std::string(*value);
		for (int decimal: decimals)
			out << "\e[2m,\e[0m " << decimal;
		return out.str();
	}

// ResumeNode

	ResumeNode::ResumeNode(ASTNode *type_, ASTNode *value_) {
		type = getType(type_);
		value = getValue(value_);
	}

	ResumeNode::~ResumeNode() {
		delete type;
		delete value;
	}

	std::string ResumeNode::debugExtra() const {
		return "\e[91mresume\e[0m " + std::string(*type) + " " + std::string(*value);
	}
}
