#include <memory>
#include <iterator>
#include <cmath>
//used "find" function implementation in lower bound and upper bound, as well as different pseudo codes 
//and articles for implementation
template<class T>
class BinarySearchTree {
public:
	class Node; // Declaration of a class.

	class iterator {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::ptrdiff_t difference_type;

		friend class BinarySearchTree;
		// ++iter
		iterator& operator++() {
			if (this->node->right_child != nullptr) {
				*this = tree.begin(this->node->right_child.get());
				return *this;
			}
			// Go up until you went up from a left child.
			while (true) {
				Node* parent = node->parent;
				if (parent == nullptr) {
					*this = tree.end();
					return *this;
				}
				if (parent->left_child.get() == this->node) {
					this->node = parent;
					return *this;
				}
				node = parent;
			}
		}

		// iter++
		iterator operator++(int) {
			iterator copy = *this;
			++(*this);
			return copy;
		}

		// --iter
		iterator& operator--() {                                               // <-----------------HW7 operator--
			if (this->node->left_child != nullptr) {
				*this = tree.rbegin(this->node->left_child.get());
				return *this;
			}
			// Go up until you went up from a left child.
			while (true) {
				Node* parent = node->parent;
				if (parent == nullptr) {
					*this = tree.end();
					return *this;
				}
				if (parent->right_child.get() == this->node) {
					this->node = parent;
					return *this;
				}
				node = parent;
			}
		};   // 1 point.

			 // iter--
		iterator operator--(int) {
			iterator copy = *this;
			--(*this);
			return copy;
		}

		// Dereferencing the iterator to get the value inside.
		// (*iter)
		const T& operator*() {
			return node->get();
		}

		// Compare to another iterator
		// iter1 == iter2.
		bool operator==(const iterator& other) {
			return node == other.node;
		}

		bool operator!=(const iterator& other) {
			return node != other.node;
		}
		// Copy the current iterator.
		iterator& operator=(const iterator& other) {
			node = other.node;
			return *this;
		}

	private:
		iterator(BinarySearchTree& tree, Node * node)
			: node(node)
			, tree(tree) {

		}
	private:
		Node* node;
		BinarySearchTree& tree;

	};

	BinarySearchTree()
		: size_(0) {

	}

	// Iterator to the start of container - from leftmost node.
	iterator begin() {
		return begin(head.get());
	}

	// Iterator to the element AFTER the last element of container.
	iterator end() {
		return iterator(*this, nullptr);
	}

	// Iterator - begin from the rightmost node.
	iterator rbegin() { // 0.5 points                                       < ------------ - HW7 rbegin();
		return rbegin(head.get());
	}

	// Iterator to the element AFTER the last element of container.
	iterator rend() {
		return end();
	}

	// Returns the size of the container.
	int size() const {
		return size_;
	}

	// Inserts the new value.
	void insert(const T& value) {
		++size_;
		if (size_ == 1) {
			head = std::make_shared<Node>(
				value,
				std::shared_ptr<Node>(),
				std::shared_ptr<Node>(),
				nullptr);
			return;
		}
		insert(head, value);
	}

	bool is_empty() const {
		return size_ == 0;
	}

	// Search for exact matches.
	iterator find(const T& value) {
		if (is_empty())
			return end();
		return find(head, value);
	}

	// Search for set member <= value.
	iterator lower_bound(const T& value) { // 1 point   <----------- HW7 lower_bound
		int arj = INT_MIN;
		return lower_b(head, value, arj);
	}
	// Search for set member > value.
	iterator upper_bound(const T& value) { // 1 point           <----------- HW7 upper_bound
		int arj = INT_MAX;
		return upper_b(head, value, arj);
	}

	// Erases element at given location.
	void erase(const T& value) { // 2 extra points				<----------- HW7 erase
		if(erase(head, value))
			size_--;
	}
private:

	class Node {
	public:
		Node(const T& value,
			std::shared_ptr<Node> left_child = nullptr,
			std::shared_ptr<Node> right_child = nullptr,
			Node* parent = nullptr)
			: value(value)
			, left_child(left_child)
			, right_child(right_child)
			, parent(parent) {

		}

		const T& get() const {
			return value;
		}

		T value;
		std::shared_ptr<Node> left_child;
		std::shared_ptr<Node> right_child;

		// We don't OWN this parent pointer;
		Node* parent;
	};

private:
	iterator begin(Node* current) {
		if (is_empty())
			return end();
		while (current->left_child != nullptr) {
			current = current->left_child.get();
		}
		return iterator(*this, current);
	}

	iterator rbegin(Node* current) {                          //   <--------rbegin()
		if (is_empty())
			return end();
		while (current->right_child != nullptr) {
			current = current->right_child.get();
		}
		return iterator(*this, current);
	}

	void insert(std::shared_ptr<Node>& current_node, const T& value) {
		if (current_node->get() == value)
			return;
		if (current_node->get() < value) {
			if (!current_node->right_child) {
				current_node->right_child = std::make_shared<Node>(value);
				current_node->right_child->parent = current_node.get();
			}
			else {
				insert(current_node->right_child, value);
			}
		}
		else {
			if (!current_node->left_child) {
				current_node->left_child = std::make_shared<Node>(value);
				current_node->left_child->parent = current_node.get();
			}
			else {
				insert(current_node->left_child, value);
			}
		}
	}

	iterator find(std::shared_ptr<Node>& current_node, const T& search_value) {
		if (current_node->get() == search_value)
			return iterator(*this, current_node.get());
		if (current_node->get() < search_value) {
			if (!current_node->right_child) {
				return end();
			}
			else {
				return find(current_node->right_child, search_value);
			}
		}
		else {
			if (!current_node->left_child) {
				return end();
			}
			else {
				return find(current_node->left_child, search_value);
			}
		}
	}

	iterator lower_b(std::shared_ptr<Node>& current_node, const T& search_value, int arj) {    // <-------new lower bound
		if (*(begin()) > search_value)
			return end();

		if (current_node->get() == search_value) {  //if it is from our tree than all left is too -- current_node
				iterator iter = iterator(*this, current_node.get());
				return iter;
		}
	 	if (current_node->get() < search_value) {
			if (!current_node->right_child) {      //does not have a right child
				if (current_node->get() <= search_value) { //value less than search value
						if(arj < current_node->get()){
					return iterator(*this, current_node.get());
					}			
				}
				else {
					auto iter3 = find(head, arj);
					return iter3;
				}
			}
			else {
				if (current_node->get() <= search_value) {
					if(arj < current_node->get()){
					arj = current_node->get();
					//return lower_b(current_node->right_child, search_value, arj);
					}
				}
				return lower_b(current_node->right_child, search_value, arj);
			}
	}
		else {
			if (!current_node->left_child) {  //no left child
				if (current_node->get() <= search_value){
					if(arj < current_node->get()){
					
					return iterator(*this, current_node.get());
					}
				}
				else {
					auto iter4 = find(head, arj);
					return iter4;
				}
			}
			else { //there is a left child
				if (current_node->get() <= search_value) {
					if(arj < current_node->get()){
					arj = current_node->get();
					//return lower_b(current_node->left_child, search_value, arj);
					}
				}
				return lower_b(current_node->left_child, search_value, arj);
			}
		}
	}



/*	iterator lower_b(std::shared_ptr<Node>& current_node, const T& search_value, Node* used) {     //<-------------- lower_b()

		if (*(begin()) <= search_value) {
			
			if (current_node->get() >= search_value) {
				used = current_node.get();
				//iterator iter3 = iterator(*this, current_node.get());
				lower_b(current_node->left_child, search_value, used);
			}
			else {
				lower_b(current_node->right_child, search_value, used);
			}
			return iterator(*this, used);
		}
		else {
			end();
		}
	};
	iterator upper_b(std::shared_ptr<Node>& current_node, const T& search_value, Node* upper) {   // <---------------upper_b()
		if (*(rbegin()) <= search_value) {     
			if (current_node->get() > search_value) {
				upper = current_node.get();
				upper_b(current_node->left_child, search_value, upper);
			}
			else {
				upper_b(current_node->right_child, search_value, upper);
			}
			return iterator(*this, upper);
		}
		else {
			end();
}		}
*/	

	iterator upper_b(std::shared_ptr<Node>& current_node, const T& search_value, int arj) { //the same way lower_b   <-----new upper bound
		if (*(rbegin()) < search_value)
			return end();

		if (current_node->get() == search_value) {  //if it is from our tree than all left is too ++ current_node
			iterator iter = iterator(*this, current_node.get());
			++iter;
			return iter;
		}
		if (search_value > current_node->get()) {
			if (!current_node->right_child) {      //does not have a right child
				if (current_node->get() >= search_value) { //value greater than search value
					if(current_node->get() < arj){
					return iterator(*this, current_node.get());
					}
				}
				else {
					iterator iter3 = find(head, arj);
					return iter3;
				}
			}
			else {
				if (current_node->get() > search_value) {
					if(current_node->get() < arj){
					arj = current_node->get();
					//return upper_b(current_node->right_child, search_value, arj);
					}
				}
				return upper_b(current_node->right_child, search_value, arj);
			}
		}
		else {
			if (!current_node->left_child) {  //no left child
				if (current_node->get() >= search_value){
					if(current_node->get() < arj){
					return iterator(*this, current_node.get());
					}
				}
				else {
					iterator iter4 = find(head, arj);
					return iter4;
				}
			}
			else { //there is a left child
				if (current_node->get() >= search_value) {
					if(current_node->get() < arj){
					arj = current_node->get();
					//return upper_b(current_node->left_child, search_value, arj);
					}
				}
				return upper_b(current_node->left_child, search_value, arj);
			}
		}
	}

	bool erase(std::shared_ptr<Node>& current_node, const T& value) {
		if (is_empty()) {
			return false;
		}
		if (value < current_node->get()) {
			return erase(current_node->left_child, value);
		}
		if (value > current_node->get()) {
			return erase(current_node->right_child, value);
		}
		if (current_node->left_child == nullptr || current_node->right_child == nullptr) {
			std::shared_ptr<Node>& used_node = current_node;
			if(current_node->parent->left_child == nullptr){
				current_node->parent->left_child = nullptr;
			}
			
		    current_node->parent->right_child = nullptr;
			
			used_node = nullptr;
			//size_--;
			return true;
		}
		std::shared_ptr<Node>& new_node = current_node; //if has two children
		auto iter3 = begin(new_node->right_child.get()); //find in right subtree the leftmost 
		current_node->value = *iter3;
		return erase(current_node->right_child, current_node->get());

	};


private:
	// The head of the tree.
	std::shared_ptr<Node> head;

	int size_;
};