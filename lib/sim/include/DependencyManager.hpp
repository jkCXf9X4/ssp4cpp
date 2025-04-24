#ifndef DEPENDENCYMANAGER_HPP
#define DEPENDENCYMANAGER_HPP

#include <list>

class DependencyManager {
public:
    void analyzeDependencies();
    std::list<int> getExecutionOrder();
};

#endif // DEPENDENCYMANAGER_HPP