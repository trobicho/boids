#pragma once
#include <vector>
#include <array>
#include <functional>
#include "boid.hpp"

#define MAX_BOID_PER_LEAF 10

class QuadtreeBaseClass {
  public:
    QuadtreeBaseClass(Vec2f min, Vec2f max) {
      m_min = min;
      m_max = max;
      m_center = (m_max - m_min) / 2.0;
    }
    virtual ~QuadtreeBaseClass(){};

    virtual bool  isLeaf() = 0;
    virtual void  addElem(Boid& elem) = 0;
    virtual void  addElem(std::vector<std::reference_wrapper<Boid>> elem) = 0;

  protected:
    Vec2f   m_center, m_min, m_max;
};

class QuadtreeBranch;

class QuadtreeLeaf: public QuadtreeBaseClass {
  public:
    QuadtreeLeaf(Vec2f min, Vec2f max): QuadtreeBaseClass(min, max){};
    ~QuadtreeLeaf(){};

    size_t  elemCount() {return (m_elements.size());}
    bool    isLeaf() {return (true);}
    void    addElem(Boid& elem) {
      m_elements.push_back(elem);
    }
    void    addElem(std::vector<std::reference_wrapper<Boid>> elements) {
      for (auto& elem : elements) {
        m_elements.push_back(elem);
      }
    }
    std::vector<std::reference_wrapper<Boid>>   getElemVector(){return(m_elements);}

  private:
    std::vector<std::reference_wrapper<Boid>>   m_elements;
    QuadtreeBranch*                             m_parent = nullptr;
};

class QuadtreeBranch: public QuadtreeBaseClass {
  public:
    QuadtreeBranch(Vec2f min, Vec2f max): QuadtreeBaseClass(min, max) {
    QuadtreeBaseClass* test = static_cast<QuadtreeBaseClass*>(new QuadtreeLeaf(m_min, m_min));
      m_childs[0] = new QuadtreeLeaf(m_min,  m_center);
      m_childs[1] = new QuadtreeLeaf(Vec2f(m_center.x, m_min.y),  Vec2f(m_max.x, m_center.y));
      m_childs[2] = new QuadtreeLeaf(Vec2f(m_min.x, m_center.y),  Vec2f(m_center.x, m_max.y));
      m_childs[3] = new QuadtreeLeaf(m_center,  m_max);
    };
    ~QuadtreeBranch(){};

    bool  isLeaf() {return (false);}

    void    addElem(std::vector<std::reference_wrapper<Boid>> elements) {
      for (auto& elem: elements) {
        addElem(elem);
      }
    }
    void  addElem(Boid& elem) {
      QuadtreeBaseClass* child = nullptr;
      if (elem.position.y < m_center.y) {
        if (elem.position.x < m_center.x)
          child = m_childs[0];
        else
          child = m_childs[1];
      }
      else {
        if (elem.position.x < m_center.x)
          child = m_childs[2];
        else
          child = m_childs[3];
      }
      child->addElem(elem);
      if (child->isLeaf()) {
        QuadtreeLeaf* childLeaf = static_cast<QuadtreeLeaf*>(child);
        if (childLeaf->elemCount() > MAX_BOID_PER_LEAF) {
          auto elements = childLeaf->getElemVector();
          childLeaf->addElem(elements);
        }
      }
    }

  private:
    std::array<QuadtreeBaseClass*, 4> m_childs;
    QuadtreeBranch*                   m_parent = nullptr;
};
