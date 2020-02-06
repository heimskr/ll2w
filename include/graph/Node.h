#ifndef NODE_H_
#define NODE_H_

#include <any>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace LL2W {
	class Graph;

	class Node {
		friend class Graph;

		public:
			struct Node_less {
				bool operator()(Node *left, Node *right) const {
					return left->index() < right->index();
				}
			};

		private:
			Graph *parent;
			std::string label_;
			std::set<Node *, Node_less> out_;
			std::set<Node *, Node_less> in_;
			int index_ = -1;

		public:
			using Map = std::unordered_map<Node *, std::unordered_set<Node *>>;
			using Set = std::set<Node *, Node_less>;

			std::any data;

			Node() = delete;
			Node(Node &&) = delete;
			Node(const Node &) = delete;
			Node & operator=(Node &&) = delete;
			Node & operator=(const Node &) = delete;

			/** Creates a node with a parent graph and a given label. */
			Node(Graph *, const std::string &);

			template <typename T>
			T * get() const {
				return static_cast<T *>(data);
			}

			/** Returns a const reference to the node's label. */
			const std::string & label() const;

			/** Changes the node's label. */
			Node & rename(const std::string &);

			/** Returns whether the node is connected to itself. */
			bool reflexive() const;

			/** Adds an edge (unidirectional by default) to another node. Returns true if the edge already existed. */
			bool link(Node &, bool bidirectional = false);
			/** Adds an edge (unidirectional by default) to another node. Returns true if the edge already existed. */
			bool link(Node *, bool bidirectional = false);

			/** Removes a edge (and optionally the opposite edge) between this node and another.
			 *  Returns true if the edge existed and was removed. */
			bool unlink(Node &, bool bidirectional = false);
			/** Removes a edge (and optionally the opposite edge) between this node and another.
			 *  Returns true if the edge existed and was removed. */
			bool unlink(Node *, bool bidirectional = false);
			/** Removes all edges from this node. */
			void unlink();

			/** Returns whether the node lacks any neighbors. */
			bool isolated() const;

			/** Should be called whenever a node's index in the parent graph changes. */
			void dirty();

			/** Returns the node's index in the parent graph. */
			int index();

			/** Returns a const set of the node's outward edges. */
			const Set & out() const;

			/** Returns a const set of the node's inward edges. */
			const Set & in() const;

			/** Adds a neighbor. */
			Node & operator+=(Node &);
			/** Adds a neighbor. */
			Node & operator+=(Node *);

			/** Removes a neighbor. */
			Node & operator-=(Node &);
			/** Removes a neighbor. */
			Node & operator-=(Node *);
			/** Removes a neighbor with a given label. */
			Node & operator-=(const std::string &);

			decltype(out_)::iterator begin();
			decltype(out_)::iterator end();

			decltype(in_)::iterator ibegin();
			decltype(in_)::iterator iend();
	};

	std::ostream & operator<<(std::ostream &, const Node &);
}

#endif
