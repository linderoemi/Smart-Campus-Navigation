#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include <vector>

struct DepartmentNode {
    std::string name;
    DepartmentNode* parent;
    std::vector<DepartmentNode*> children;
);
class DepartmentTree {
private:
    DepartmentNode* root;
public:
    DepartmentTree();
    ~DepartmentTree();
    DepartmentTree)const DepartmentTree&) = delete;
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





