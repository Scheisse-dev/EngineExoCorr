#include "Selection.h"

Engine::Selection::Selection(const Selection& _copy) = default;


void Engine::Selection::SetSelection(Object* _obj)
{
    if (selected == _obj) return;
    selected = _obj;
    OnSelectionChanged.Invoke(selected);
}
Engine::Object* Engine::Selection::GetSelected()
{
    return selected;
}
