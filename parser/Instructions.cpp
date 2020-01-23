#include <iostream>
#include <sstream>

#include "Instructions.h"
#include "StringSet.h"

namespace LL2W {

// SelectNode

	SelectNode::SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type,
	                       ASTNode *condition_value, ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2) {
		result = StringSet::intern(result_->extractName());
		delete result_;

		for (ASTNode *child: *fastmath_) {
			const std::string &fmname = *child->lexerInfo;
			for (const std::pair<Fastmath, std::string> &pair: fastmath_map) {
				if (fmname == pair.second) {
					fastmath.insert(pair.first);
					break;
				}
			}
		}
		delete fastmath_;

		conditionType = getType(condition_type);
		delete condition_type;

		conditionValue = getValue(condition_value);
		delete condition_value;

		firstType = getType(type1);
		delete type1;

		firstValue = getValue(val1);
		delete val1;

		secondType = getType(type2);
		delete type2;

		secondValue = getValue(val2);
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
		out << "\e[32m%" << *result << " \e[2m= \e[0;91mselect\e[0;38;5;202m";
		for (Fastmath flag: fastmath)
			out << " " << fastmath_map.at(flag);
		out << " " << std::string(*conditionType) << " " << std::string(*conditionValue) << "\e[2m,\e[0m "
		    << std::string(*firstType) << " " << std::string(*firstValue) << "\e[2m,\e[0m " << std::string(*secondType)
		    << " " << std::string(*secondValue);
		return out.str();
	}

// AllocaNode

	AllocaNode::AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
	                       ASTNode *addrspace_) {
		result = StringSet::intern(result_->extractName());
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
			align = atoi(align_->lexerInfo->c_str());
			delete align_;
		}

		if (addrspace_) {
			addrspace = atoi(addrspace_->lexerInfo->c_str());
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
		if (numelementsType)
			out << "\e[2m,\e[0m " << std::string(*numelementsType) << " " << std::string(*numelementsValue);
		if (align != -1)
			out << "\e[2m,\e[0;34m align\e[0m " << align;
		if (addrspace != -1)
			out << "\e[2m,\e[0;34m addrspace\e[0m(" << addrspace << ")";
		return out.str();
	}

// StoreNode

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *ptr_type, ASTNode *ptr_index,
	                     ASTNode *align_, ASTNode *nontemporal_, ASTNode *invariant_group) {
		atomic = false;

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		type = getType(type_);
		delete type_;

		value = getValue(value_);
		delete value_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		ptrIndex = atoi(ptr_index->lexerInfo->substr(1).c_str());
		delete ptr_index;

		if (align_) {
			align = atoi(align_->lexerInfo->c_str());
			delete align_;
		}

		if (nontemporal_) { // TOK_INTBANG "!42"
			nontemporalIndex = atoi(nontemporal_->lexerInfo->substr(1).c_str());
			delete nontemporal_;
		}

		if (invariant_group) { // Same as above
			invariantGroupIndex = atoi(invariant_group->lexerInfo->substr(1).c_str());
			delete invariant_group;
		}
	}

	StoreNode::StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *ptr_type, ASTNode *ptr_index,
	                     ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group) {
		atomic = true;

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		type = getType(type_);
		delete type_;

		value = getValue(value_);
		delete value_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		ptrIndex = atoi(ptr_index->lexerInfo->substr(1).c_str());
		delete ptr_index;

		if (syncscope_) {
			syncscope = StringSet::intern(syncscope_->extractName());
			delete syncscope_;
		}

		const std::string &oname = *ordering_->lexerInfo;
		for (const std::pair<Ordering, std::string> &pair: ordering_map) {
			if (oname == pair.second) {
				ordering = pair.first;
				break;
			}
		}
		delete ordering_;

		align = atoi(align_->lexerInfo->c_str());
		delete align_;

		if (invariant_group) {
			invariantGroupIndex = atoi(invariant_group->lexerInfo->substr(1).c_str());
			delete invariant_group;
		}
	}

	StoreNode::~StoreNode() {
		delete type;
		delete value;
		delete ptrType;
	}

	std::string StoreNode::debugExtra() const {
		std::stringstream out;
		out << "\e[91mstore\e[0m";
		if (atomic)
			out << " \e[38;5;202matomic\e[0m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[0m";
		out << "\e[0m " << std::string(*type) << " " << std::string(*value) << "\e[2m,\e[0m " << std::string(*ptrType)
		    << " \e[32m%" << ptrIndex << "\e[0m";
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

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *ptr_type, ASTNode *ptr_index,
	                   ASTNode *align_, ASTNode *nontemporal_, ASTNode *invariant_load, ASTNode *invariant_group,
	                   ASTNode *nonnull_, ASTNode *dereferenceable_, ASTNode *dereferenceable_or_null,
	                   ASTNode *bang_align) {
		atomic = false;

		result = StringSet::intern(result_->extractName());

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		type = getType(type_);
		delete type_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		ptrIndex = atoi(ptr_index->lexerInfo->substr(1).c_str());
		delete ptr_index;

		if (align_) {
			align = atoi(align_->lexerInfo->c_str());
			delete align_;
		}

		if (nontemporal_) {
			nontemporalIndex = atoi(nontemporal_->lexerInfo->substr(1).c_str());
			delete nontemporal_;
		}

		if (invariant_load) {
			invariantLoadIndex = atoi(invariant_load->lexerInfo->substr(1).c_str());
			delete invariant_load;
		}

		if (invariant_group) {
			invariantGroupIndex = atoi(invariant_group->lexerInfo->substr(1).c_str());
			delete invariant_group;
		}

		if (nonnull_) {
			nonnullIndex = atoi(nonnull_->lexerInfo->substr(1).c_str());
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

	LoadNode::LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *ptr_type, ASTNode *ptr_index,
	                   ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group) {
		atomic = true;

		result = StringSet::intern(result_->extractName());

		if (volatile__) {
			volatile_ = true;
			delete volatile__;
		}

		type = getType(type_);
		delete type_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		ptrIndex = atoi(ptr_index->lexerInfo->substr(1).c_str());
		delete ptr_index;

		if (syncscope_) {
			syncscope = StringSet::intern(syncscope_->extractName());
			delete syncscope_;
		}

		const std::string &oname = *ordering_->lexerInfo;
		for (const std::pair<Ordering, std::string> &pair: ordering_map) {
			if (oname == pair.second) {
				ordering = pair.first;
				break;
			}
		}
		delete ordering_;

		align = atoi(align_->lexerInfo->c_str());
		delete align_;

		if (invariant_group) {
			invariantGroupIndex = atoi(invariant_group->lexerInfo->substr(1).c_str());
			delete invariant_group;
		}
	}

	LoadNode::~LoadNode() {
		delete type;
		delete ptrType;
	}

	std::string LoadNode::debugExtra() const {
		std::stringstream out;
		out << "\e[32m%" << *result << "\e[0;2m = \e[0;91mload\e[0m";
		if (atomic)
			out << " \e[38;5;202matomic\e[0m";
		if (volatile_)
			out << " \e[38;5;202mvolatile\e[0m";
		out << "\e[0m " << std::string(*type) << "\e[2m,\e[0m " << std::string(*ptrType)
		    << " \e[32m%" << ptrIndex << "\e[0m";
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

	IcmpNode::IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op1, ASTNode *op2) {
		result = StringSet::intern(result_->extractName());
		delete result_;

		for (const std::pair<IcmpCond, std::string> &pair: cond_map) {
			if (*cond_->lexerInfo == pair.second) {
				cond = pair.first;
				break;
			}
		}

		type = getType(type_);
		delete type_;

		value1 = getValue(op1);
		delete op1;

		value2 = getValue(op2);
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

	std::string BrUncondNode::debugExtra() const {
		return "\e[91mbr\e[0;34m label \e[32m" + *destination + "\e[0m";
	}

	BrCondNode::BrCondNode(const ASTNode *type, const ASTNode *condition_, const ASTNode *if_true,
	                       const ASTNode *if_false) {
		if (*type->lexerInfo != "i1")
			yyerror("Expected i1 for br condition type");
		condition = getValue(condition_);
		delete condition_;
		ifTrue = if_true->lexerInfo;
		delete if_true;
		ifFalse = if_false->lexerInfo;
		delete if_false;
	}

	BrCondNode::~BrCondNode() {
		delete condition;
	}

	std::string BrCondNode::debugExtra() const {
		return "\e[91mbr \e[33mi1\e[39m " + std::string(*condition) + ", label \e[32m" + *ifTrue + "\e[39m, label "
			"\e[32m" + *ifFalse + "\e[39m";
	}

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
				dereferenceable = atoi(child->at(0)->lexerInfo->c_str());
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
			addrspace = atoi(_addrspace->at(0)->lexerInfo->c_str());
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
			attributeIndices.push_back(atoi(child->lexerInfo->c_str()));
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

	CallNode::CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv,
	                   ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args,
	                   ASTNode *function_name, ASTNode *_constants, ASTNode *attribute_list):
	                   CallInvokeNode(_result, _cconv, _retattrs, _addrspace, return_type, _args, function_name,
	                                  _constants, attribute_list) {
		if (_tail) {
			tail = _tail->lexerInfo;
			delete _tail;
		}

		for (ASTNode *child: *fastmath_flags) {
			const std::string &fmname = *child->lexerInfo;
			for (const std::pair<Fastmath, std::string> &pair: fastmath_map) {
				if (fmname == pair.second) {
					fastmath.insert(pair.first);
					break;
				}
			}
		}
		delete fastmath_flags;
	}

	std::string CallNode::debugExtra() const {
		std::stringstream out;
		if (result)
			out << "\e[32m%" << *result << "\e[0;2m = ";
		if (tail)
			out << "\e[0;34m" << *tail << " ";
		out << "\e[0;91mcall\e[0m";
		for (Fastmath flag: fastmath)
			out << " \e[34m" << fastmath_map.at(flag) << "\e[0m";
		if (!fastmath.empty())
			out << "\e[0;2m .\e[0m";
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
		out << "\e[2m)\e[0m";
		return out.str();
	}

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

	GetelementptrNode::GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *ptr_type,
	                                     ASTNode *ptrval, ASTNode *indices_) {
		result = StringSet::intern(pvar->extractName());
		delete pvar;

		if (_inbounds) {
			inbounds = true;
			delete _inbounds;
		}

		type = getType(type_);
		delete type_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		ptrValue = StringSet::intern(ptrval->extractName());
		delete ptrval;

		for (ASTNode *comma: *indices_) {
			indices.push_back({
				atoi(comma->at(0)->lexerInfo->substr(1).c_str()),
				atoi(comma->at(1)->lexerInfo->c_str()),
				comma->size() == 3});
		}
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

	RetNode::RetNode(): type(new VoidType()), value(new VoidValue()) {}

	RetNode::RetNode(ASTNode *type_, ASTNode *value_) {
		type = getType(type_);
		delete type_;

		value = getValue(value_);
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
}
