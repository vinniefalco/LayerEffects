/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

#ifndef VF_BINARY_TREE_H
#define VF_BINARY_TREE_H

#include "../memory/fixed_pool.h"

/*
concept Index
{
public:
  typedef string key_t;
  typedef Track* elem_t;
  typedef uint32_t hash_t;

  static hash_t hash (const key_t& key);
  static const key_t key (const elem_t& element);
};
*/

// binary tree
// - randomized insertion (i.e. self-balancing)
// - optimized memory layout
// - "find or add" hint optimization
// - deletion is disallowed

template <class Index>
class binary_tree
{
public:
  typedef typename Index::key_t key_t;
  typedef typename Index::elem_t elem_t;
  typedef typename Index::hash_t hash_t;

  binary_tree (int pageBytes = 65536)
    : m_pool (pageBytes)
    , m_root (0)
    , m_hint (0)
    , m_depth (0)
    , m_size (0)
  {
  }

  elem_t const* find (const key_t& key)
  {
    node_t* cur = m_root;
    if (cur)
    {
      hash_t hash = Index::hash (key);

      int depth = 0;

      while (cur)
      {
        depth++;
        if (depth > m_depth)
          m_depth = depth;

        m_hint = cur;

        if (hash > cur->hash)
        {
          cur = cur->right;
          m_hint_dir = 1;
        }
        else if (hash < cur->hash)
        {
          cur = cur->left;
          m_hint_dir = -1;
        }
        else
        {
          // generate key once for speed
          const key_t& comp = Index::key (cur->elem);

          if (key > comp)
          {
            cur = cur->right;
            m_hint_dir = 1;
          }
          else if (key < comp)
          {
            cur = cur->left;
            m_hint_dir = -1;
          }
          else
          {
            m_hint_dir = 0;

            // match
            return &cur->elem;
          }
        }
      }
    }

    return 0;
  }

  void insert (const elem_t& elem)
  {
    const elem_t* found = find (Index::key (elem));

    if (found)
      throw (std::logic_error("duplicate in binary_tree"));

    node_t* node = m_pool.alloc ();
    node->elem = elem;
    node->hash = Index::hash (Index::key (elem));
    node->left = 0;
    node->right = 0;
    m_size++;

    if (m_hint)
    {
      if (m_hint_dir == 1)
        m_hint->right = node;
      else if (m_hint_dir == -1)
        m_hint->left = node;
      else
        throw (std::logic_error("duplicate in binary_tree"));
    }
    else
    {
      m_root = node;
    }
  }

private:
  struct node_t
  {
    elem_t elem;
    hash_t hash;
    node_t* left;
    node_t* right;
  };

  fixed_pool <node_t> m_pool;
  node_t* m_root;
  node_t* m_hint; // for insertion
  int m_hint_dir;
  int m_depth;
  int m_size;
};

#endif
