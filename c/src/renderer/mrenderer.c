
#include "mangopub.h"

/**
 * Renders a node and all its children completely.
 * \param   node    Node being rendered.
 * \param   context Initial context to use for variable resolution
 * \param   output  Output stream to write the rendered output to.
 * \param   error   Error to be set if any.
 * \return  0   if successful, otherwise error.
 */
int mango_render_node(MangoNode *node,
                      MangoTemplateContext *context, 
                      MangoOutStream *outstream,
                      MangoError **error)
{
    MangoNode *currNode             = NULL;
    MangoNode *nextNode             = NULL;
    MangoNodeContext *currContext   = NULL;
    MangoList *inputNodes           = (MangoList *)mango_linkedlist_new();
    LIST_PUSH_FRONT(inputNodes, node);
  
    while (!COLLECTION_IS_EMPTY(inputNodes))
    {
        if (currNode == NULL)
        {
            nextNode = currNode = (MangoNode *)LIST_POP_FRONT(inputNodes);
            MangoNodeContext *newContext = mango_node_create_context(currNode, context, currContext);
            if (newContext == NULL)
                newContext = mango_nodecontext_new(currNode, currContext);
            currContext = newContext;
        }
  
        while (nextNode == currNode)
        {
            nextNode = mango_node_render_bit_more(currNode, outstream, context, currContext, error);
            if (error != NULL)
            {
                OBJ_DECREF(inputNodes);
                return -1;
            }
        }

        if (nextNode != NULL)
        {
            // push the new node into the stack so it will
            // continued from the next time
            LIST_PUSH_FRONT(inputNodes, nextNode);
            currNode = NULL;
        }
        else 
        {
            // we are exiting out of the node so go the parent
            // to see what to do on a child node exit
            while (nextNode == NULL && currContext->parent != NULL)
            {
                nextNode        = mango_node_child_exited(currContext->parent->node, currNode, context, currContext->parent, error);
                if (error != NULL)
                {
                    OBJ_DECREF(inputNodes);
                    return -1;
                }
                currContext     = currContext->parent;
                currNode        = nextNode;
            }

            currNode = NULL;
            if (nextNode != NULL)
            {
                LIST_PUSH_FRONT(inputNodes, nextNode);
            }
            else
            {
                currContext = currContext->parent;
            }
        }
    }
    return 0;
}
