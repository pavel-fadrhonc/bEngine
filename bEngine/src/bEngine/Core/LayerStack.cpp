#include "bepch.h"
#include "LayerStack.h"

bEngine::LayerStack::LayerStack()
{
    
}

bEngine::LayerStack::~LayerStack()
{
    for (auto layer : m_Layers)
    {
        delete layer;
    }
}

void bEngine::LayerStack::PushLayer(Layer* layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
}

void bEngine::LayerStack::PushOverlay(Layer* overlay)
{
    m_Layers.emplace_back(overlay);
}

void bEngine::LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void bEngine::LayerStack::PopOverlay(Layer* overlay)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}
