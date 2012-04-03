//
//  TreeNode.h
//  livedraw
//
//  Created by Christopher Baker on 4/2/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once


using namespace std;

template<typename T>
class TreeNode {
    
public:
    
    bool addTreeChild(T* child);
    T* getTreeParent();
    
    vector<T*> getTreeChildren();
    
private:
    
    T* treeParent;
    vector<T*> treeChildren;

};

