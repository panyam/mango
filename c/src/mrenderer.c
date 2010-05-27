
#include "mrenderer.h"

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
                      MangoOutputStream *outstream,
                      MangoError **error)
{
    MangoNode *currNode = NULL;
    MangoNode *nextNode = NULL;
    NodeContext currContext = NULL;
    Stack<Node> inputNodes = new Stack<Node>();
    inputNodes.push(node);
  
    while (!inputNodes.empty())
    {
        if (currNode == NULL)
        {
            nextNode = currNode = inputNodes.pop();
            NodeContext newContext = currNode.createNodeContext(context, currContext);
            if (newContext == NULL)
                newContext = new NodeContext(currNode, currContext);
            currContext = newContext;
        }
  
        while (nextNode == currNode)
        {
            nextNode = currNode.renderBitMore(writer, context, currContext);
        }

        if (nextNode != NULL)
        {
            // push the new node into the stack so it will
            // continued from the next time
            inputNodes.push(nextNode);
            currNode = NULL;
        }
        else 
        {
            // we are exiting out of the node so go the parent
            // to see what to do on a child node exit
            while (nextNode == NULL && currContext.parent != NULL)
            {
                nextNode        = currContext.parent.node.childExited(currNode, context, currContext.parent);
                currContext     = currContext.parent;
                currNode        = nextNode;
            }

            currNode = NULL;
            if (nextNode != NULL)
            {
                inputNodes.push(nextNode);
            }
            else
            {
                currContext = currContext.parent;
            }
        }
    }
}
