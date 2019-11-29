#include <cstdlib>
#include <iostream>
#include <memory>
 
#include "Triangle.h"
#include "TStackItem.h"
#include "TStack.h"
 
 
#include "TAllocationBlock.h"
 
void TestStack()
{
    TStack<Triangle> stack;
    
    stack.push(std::shared_ptr<Triangle>(new Triangle(1,1,1)));
    stack.push(std::shared_ptr<Triangle>(new Triangle(2,2,2)));
    stack.push(std::shared_ptr<Triangle>(new Triangle(3,3,3)));
    stack.push(std::shared_ptr<Triangle>(new Triangle(3,3,3)));
 
    
    for(auto i : stack)  std::cout << *i << std::endl;
    
    
    std::shared_ptr<Triangle> t;
    
    while(!stack.empty()) std::cout <<  *stack.pop() << std::endl;
}
