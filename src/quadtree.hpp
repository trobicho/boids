#pragma once
#include "boid.hpp"

#define MAX_BOID_PER_LEAF 10

class QuadtreeBaseClass {
  public:
    QuadtreeBaseClass(Vec2f min, Vec2f max) {
      m_min = min;
      m_max = max;
      m_center = (m_max - m_min) / 2.0;
    }
    virtual bool  isLeaf() = 0;
    virtual void  addElem(Boid& elem) = 0;

  private:
    Vec2f   m_center, m_min, m_max;
};

class QuadtreeBranch;

class QuadtreeLeaf: public QuadtreeBaseClass {
  public:
    QuadtreeLeaf(Vec2f min, Vec2f max): QuadtreeBaseClass(min, max){};
    ~QuadtreeLeaf(){};

    QuadtreeBranch* split(); {
      QuadtreeBranch* newBranch = new QuadtreeBranch(m_min, m_max);

      for (auto &elem : m_elements) {
        newBranch.addElem(elem);
      }
      return (newChilds);
    }

    bool  isLeaf() {return (true);};
    void  addElem(Boid& elem) {
      m_elements.push(elem);
    }

  private:
    std::vec<Boid&>   m_elements;
    QuadtreeBranch*   m_parent = nullptr;
};

class QuadtreeBranch: public QuadtreeBaseClass {
  public:
    QuadtreeBranch(Vec2f min, Vec2f max): QuadtreeBaseClass(min, max) {
      m_childs[0] = new QuadtreeLeaf(m_min,  m_center);
      m_childs[1] = new QuadtreeLeaf(Vec2f(m_center.x, m_min.y),  Vec2f(m_max.x, m_center.y);
      m_childs[2] = new QuadtreeLeaf(Vec2f(m_min.x, m_center.y),  Vec2f(m_center.x, m_max.y);
      m_childs[3] = new QuadtreeLeaf(m_center,  m_max);
    };
    ~QuadtreeBranch(){};

    bool  isLeaf() {return (false);};
    void  addElem(Boid& elem) {
      if (elem.position.y < m_center.y) {
        if (elem.position.x < m_center.x)
          m_childs[0].addElem(elem);
        else
          m_childs[1].addElem(elem);
      }
      else {
        if (elem.position.x < m_center.x)
          m_childs[2].addElem(elem);
        else
          m_childs[3].addElem(elem);
      }
    }

  private:
    std::array<QuadtreeBaseClass*, 4> m_childs;
    QuadtreeBranch*                   m_parent = nullptr;
};

class Quadtree {
  public:
    Quadtree(){};
    ~Quadtree(){};

  private:
    std::array<QuadtreeBaseClass*, 4> m_branchs = {nullptr, nullptr, nullptr, nullptr};
};
