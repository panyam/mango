
#include "mvarresolver.h"
#include "mtemplatecontext.h"
#include "mvar.h"
#include "mvalue.h"
#include "mmemutils.h"

/**
 * The default variable resolver function.
 */
MangoValue *default_resolver_func(MangoVarResolver *resolver, MangoValue *source, MangoVar *var);

DECLARE_PROTO_FUNC("VarResolver", MangoVarResolverPrototype, mango_varresolver_prototype, 
    __proto__.resolveFunc = NULL;
);

/**
 * Returns a default var resolver.
 */
MangoVarResolver *mango_varresolver_default()
{
    static MangoVarResolver resolver;
    static BOOL initialised = false;
    if (!initialised)
    {
        OBJ_INIT(&resolver , mango_varresolver_prototype());
        initialised = true;
    }
    return &resolver;
}

/**
 * Deallocates a resolver on destruction.
 */
void mango_varresolver_dealloc(MangoVarResolver *resolver)
{
    mango_object_dealloc((MangoObject *)resolver);
}

/**
 * Resolves the var value with the resolver.
 * \param   resolver    Resolver doing the var resolving.
 * \param   source      The source var from which vars are resolved.
 * \param   var    Var to be resolved.
 * \return  A MangoValue instance that must be freed by the caller.
 */
MangoValue *mango_varresolver_resolve(MangoVarResolver *resolver,
                                      MangoValue *source,
                                      MangoVar *var)
{
    if (resolver->__prototype__->resolveFunc != NULL && var != NULL)
    {
        return resolver->__prototype__->resolveFunc(resolver, source, var);
    }
    return NULL;
}

/**
 * Resolves a var chain starting from the first var using the
 * template context.
 * \param   resolver    Main resolver object.
 * \param   ctx         Context with which the var is resolved.
 * \param   first       First var to start resolving with.
 * \return  The value corresponding to the var.
 */
MangoValue *mango_varresolver_resolve_chain(MangoVarResolver *resolver,
                                            MangoTemplateContext *ctx,
                                            MangoVar *first)
{
    // if the first item is a number then everything is ignored
    MangoVar *curr_var = first;
    MangoVar *prev_var = NULL;
    MangoValue ctx_value = mango_value_make(MV_CONTEXT, ctx);
    MangoValue *curr_src = &ctx_value;
    while (curr_src != NULL && curr_var != NULL)
    {
        if (prev_var == NULL)
        {
            if (curr_var->isNumber)
                return mango_value_new(MV_INT, (void*)curr_var->intValue);
            if (curr_var->isQuoted)
                return mango_value_new(MV_STRING,
                                        mango_string_copy(curr_var->value));
            if (ctx == NULL)
                return NULL;
            curr_src = mango_templatecontext_get(ctx, curr_var->value);
        }
        else
        {
            MangoValue *newsrc = mango_varresolver_resolve(resolver, curr_src, curr_var);
            if (curr_src != &ctx_value)
                mango_value_free(curr_src);
            curr_src = newsrc;
        }
        prev_var = curr_var;
        curr_var = curr_var->next;
    }
    return curr_src;
}

/**
 * The default variable resolver function.
 * Unlike the android based resolver which has nice introspection, we do
 * nothing fancy, just check the source value type and so on.
 */
MangoValue *default_resolver_func(MangoVarResolver *resolver, MangoValue *source, MangoVar *var)
{
    /**
     * Resolves the value of a variable using a particular value.
     * The resolution strategy used is slightly different from what django
     * does, in order to make things a bit faster for the common case of
     * dictionary and index based lookups.
     *
     * ((Array)source)[value] if value is an integer
     * ((Dictionary)source)[value] if value is NOT an integer
     *
     * Returns null if the variable cannot be resolved after applying the
     * above rules.
     */
    // try as an integer first
    BOOL performMethodAndAttributeCheck = true;
    if (var->isNumber)
    {
        int intValue = var->intValue;

        // set this flag to true so that if we fall through here and go to the map case
        // then we do not want this to be treated as a method or an attribute
        performMethodAndAttributeCheck = false;
        if (source->valueType == MV_ARRAY)
        {
            return mango_array_item_at((MangoArray *)source->valueData, intValue);
        }
        else
        {
            // convert to an array
            if (source.getClass().isArray())
            {
                return Array.get(source, intValue);
            }
            else
            {
                // worst case - see if the object has a method
                // atIndex or elementAt or something like that
                // we will go with elementAtIndex for now.
                Class<?> sourceClass = source.getClass();
                Method method = null;
                try {
                    method = sourceClass.getMethod("elementAtIndex", int.class);
                } catch (SecurityException e) {
                    e.printStackTrace();
                } catch (NoSuchMethodException e) {
                    e.printStackTrace();
                }

                if (method != null)
                {
                    try {
                        method.setAccessible(true);
                        return method.invoke(source, intValue);
                    } catch (IllegalArgumentException e) {
                        e.printStackTrace();
                    } catch (IllegalAccessException e) {
                        e.printStackTrace();
                    } catch (InvocationTargetException e) {
                        e.printStackTrace();
                    }
                }
                
                // here we fall through and let it be handled as a map/associative 
                // container of some sort
            }
        }
    }
    
    String value = variable.value;

    // try as a dictionary lookup - ie using a Map
    if (source instanceof Map<?,?> && ((Map<?,?>)source).containsKey(value))
    {
        return ((Map<?,?>)source).get(value);
    }
    if (source instanceof Hashtable<?,?> && ((Hashtable<?,?>)source).containsKey(value))
    {
        return ((Hashtable<?,?>)source).get(value);
    }
    if (source instanceof TemplateContext && ((TemplateContext)source).hasValue(value))
    {
        return ((TemplateContext)source).getValue(value);
    }

    // now check if we are a method or an attribute
    if (performMethodAndAttributeCheck)
    {
        // first check for attributes
        Class<?> sourceClass = source.getClass();
        try {
            Field field = sourceClass.getField(value);
            try {
                field.setAccessible(true);
                return field.get(source);
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
        }
        
        try {
            Method method = sourceClass.getMethod(value, (Class [])null);
            try {
                method.setAccessible(true);
                return method.invoke(source, (Object [])null);
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
        }
    }
    return NULL;
}

