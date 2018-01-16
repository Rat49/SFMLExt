#pragma once
#include <memory>
#include <SFML\Graphics.hpp>

namespace ext
{

    class GameObject
    {
    public:
        bool isUpdateEnabled() const { return m_updateEnabled; }
        bool isFixedUpdateEnabled() const { return m_fixedUpdateEnabled; }
        bool IisRenderEnabled() const { return m_renderEnabled; }
        sf::Uint32 getSpriteLayer() const { return m_spriteLayer; }
        sf::Uint32 getSpriteOrder() const { return m_spriteOrderInLayer; }

        virtual void update(float deltaTime) {}
        virtual void fixedUpdate(float deltaTime) {}

        bool isUpdateOverriden() const
        {
            return GameObject::update == this->update;
        }

        bool isFixedUpdateOverriden() const
        {
            return GameObject::fixedUpdate == this->fixedUpdate;
        }

    protected:
        bool m_updateEnabled;
        bool m_fixedUpdateEnabled;

        //to activate render you need to inherit sf::Drawable
        bool m_renderEnabled;
        sf::Uint32 m_spriteLayer;
        sf::Uint32 m_spriteOrderInLayer;
    };

    class Cycle final
    {
    public:
        Cycle(std::weak_ptr<sf::RenderWindow> wnd);

        void registerGameObject(GameObject* obj);
        void unregisterGameObject(GameObject* obj);

        void runSync();
        void runAsync();

    private:
        void execute();
        void update() const;
        void fixedUpdate() const;
        void render() const;

    private:
        std::vector<GameObject*> m_toUpdate;
        std::vector<GameObject*> m_toFixedUpdate;
        std::vector<sf::Drawable*> m_toRender;
        std::weak_ptr<sf::RenderWindow> m_window;
    };
}