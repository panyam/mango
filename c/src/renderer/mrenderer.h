
#ifndef __MANGO_RENDERER_H__
#define __MANGO_RENDERER_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * How does rendering in the nodes work?  We have 4 goals: 
 *
 * 1. Inheritable nodes for extensibility
 * 2. Incremental rendering for efficiency especially for mobile devices.
 *
 * So to do this a node cannot do its rendering.  Well it can but then it
 * will have to manage the context stacks manually.  Instead we have a
 * "renderer" that drives the rendering process and the nodes simply
 * provide information to the renderer on what kind of stack info it needs
 * to save and restore.
 *
 * Initially the renderer is given a list of nodes to render (or a
 * node list).  But the renderer cannot ask a stack to render, instead it
 * has to enter a node.  A node can be entered in two ways.
 *
 * 1. When a node is first encountered by a parent node, then its
 * enterFromParent method is called.  It is passed a template context and
 * the current context stack.  This will create its own context and push it
 * onto the context stack, return the new stack head.  At this point no
 * rendering is done.  All this does is tell the renderer that the current
 * node to render has changed (to this node).
 *
 * Should this method recursively enter the child nodes or not?
 *  - If we want to recursively enter child nodes then we have to do the
 *    recursion in every node here.  Instead if we simply pass the "next
 *    node to be entered" to the renderer somehow, it can do all that
 *    plumbing.
 *
 * 2. If we are not recursively entering the child nodes in the previous
 * step, then we enter the node. And make the node render chunks for as
 * long as it wants.  At each render it can return one of 3 things:
 *  -   this   	- nothing, just wrote some data to the writer
 *  -   null	- Rendering finished and node is done with
 *  -   node   	- Node has a child node it wants rendered (which it returns
 *            		"somehow")
 */


/**
 * Renders a node and all its children completely.
 * \param   node    Node being rendered.
 * \param   context Initial context to use for variable resolution
 * \param   output  Output stream to write the rendered output to.
 * \param   error   Error to be set if any.
 * \return  0   if successful, otherwise error.
 */
extern int mango_render_node(MangoNode *node,
                             MangoTemplateContext *context, 
                             MangoOutStream *outstream,
                             MangoError **error);

#ifdef __cplusplus
}
#endif

#endif


