#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include <vector>

using namespace std;

struct DepartmentNode {
    std::string name;
    DepartmentNode* parent;
    std::vector<DepartmentNode*> children;

    DepartmentNode(const string& departmentName, DepartmentNode* parentNode)
        : name(departmentName), parent(parentNode) {}
    };
class DepartmentTree {
private:
    DepartmentNode* root;
    void deleteTree(DepartmentNode* node);
    DepartmentNode* findDepartment(
        DepartmentNode* node,
        const string& name) const;
    string normalizeName(const string& name) const;
    string trim(const string& value) const;
  void preorderHelper(DepartmentNode* node) const;
  void displayHierarchyHelper(DepartmentNode* node, int depth) const;

public:
    DepartmentTree();
    ~DepartmentTree();
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    bool loadFromFile(const std::string& filename,
                       int& accepted,
                       int& rejected);

    bool addDepartment(const std::string& name,
                       const std::string& parentName);
    const DepartmentNode* searchDepartment(
         const std::string& name) const;

     void displayHierarchy() const;

     void displayPreorder() const;

     bool isEmpty() const;
};

#endif





