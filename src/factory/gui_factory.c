#include <factory/gui_factory.h>

static gui_factory _gui_factory = { 0 };

button *gui_factory_button_construct ( gui_factory *p_gui_factory );
label *gui_factory_label_construct ( gui_factory *p_gui_factory );

gui_factory *gui_factory_instance ( void )
{
    if ( NULL == _gui_factory.p_unique_instance )
    {
        char *env_var = getenv("UI_THEME");

        if ( env_var )
        {
            if ( 0 == strcmp(env_var, "red") ) 
                _gui_factory.p_unique_instance = red_gui_factory_instance();
            else if ( 0 == strcmp(env_var, "green") ) 
                _gui_factory.p_unique_instance = green_gui_factory_instance();
            else 
                _gui_factory.p_unique_instance = blue_gui_factory_instance();
        }
        else
            _gui_factory.p_unique_instance = blue_gui_factory_instance();
        
        _gui_factory.pfn_button_construct = gui_factory_button_construct;
        _gui_factory.pfn_label_construct = gui_factory_label_construct;
    }

    return &_gui_factory;
}

button *gui_factory_button_construct ( gui_factory *p_gui_factory )
{
    return p_gui_factory->p_unique_instance->pfn_button_construct(p_gui_factory->p_unique_instance);
}

label *gui_factory_label_construct ( gui_factory *p_gui_factory )
{
    return p_gui_factory->p_unique_instance->pfn_label_construct(p_gui_factory->p_unique_instance);
}