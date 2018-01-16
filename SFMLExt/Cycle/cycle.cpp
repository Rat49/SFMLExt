#include "cycle.h"
#include <tuple>

using namespace ext;

Cycle::Cycle(std::weak_ptr<sf::RenderWindow> wnd)
    : m_window(wnd)
{
}

void Cycle::registerGameObject(GameObject* obj)
{
    if(obj == nullptr)
    {
        return;
    }

    if(obj->isFixedUpdateOverriden())
    {
        m_toFixedUpdate.push_back(obj);
    }
    if(obj->isUpdateOverriden())
    {
        m_toUpdate.push_back(obj);
    }

    auto renderable = dynamic_cast<sf::Drawable*>(obj);
    if(renderable != nullptr)
    {
        m_toRender.push_back(renderable);

        std::sort(std::begin(m_toRender), std::end(m_toRender), [](GameObject* left, GameObject* right)
                  {
                      auto lLayer = left->getSpriteLayer();
                      auto rLayer = right->getSpriteLayer();
                      return (lLayer != rLayer) ? (lLayer < rLayer) : (left->getSpriteOrder() < right->getSpriteOrder());
                  });
    }
}

void Cycle::unregisterGameObject(GameObject* obj)
{
    if(obj == nullptr)
    {
        return;
    }

    if(obj->isFixedUpdateOverriden())
    {
        m_toFixedUpdate.erase(std::remove(std::cbegin(m_toFixedUpdate), std::cend(m_toFixedUpdate), obj), std::cend(m_toFixedUpdate));
    }
    if(obj->isUpdateOverriden())
    {
        m_toUpdate.erase(std::remove(std::cbegin(m_toUpdate), std::cend(m_toUpdate), obj), std::cend(m_toUpdate));
    }
    if(dynamic_cast<sf::Drawable*>(obj) != nullptr)
    {
    m_toRender.erase(std::remove(std::cbegin(m_toRender), std::cend(m_toRender), obj), std::cend(m_toRender));
}

void Cycle::runSync()
{
    execute();
}

void Cycle::runAsync()
{
    //start and return
}

void Cycle::execute()
{
}

void Cycle::update()
{
}

void Cycle::fixedUpdate()
{
}

void Cycle::render() const
{
    if(m_window.expired())
    {
        return;
    }

    auto wnd = m_window.lock();
    for(auto obj : m_toRender)
    {
        wnd->render(obj);
    }
}
