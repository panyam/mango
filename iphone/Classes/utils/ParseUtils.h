//
//  ParseUtils.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#import "DTForwardDefs.h"

/**
 * Utility class for parsing variables and other common elements.
 * 
 * @author Sri Panyam
 */
Variable *			parseVariable(Parser * parser, NSError **error);
NSMutableArray *	parseFilterList(Parser *parser, NSError **error);
FilterNode *		parseFilterExpression(Parser *parser, NSError **error);
BOOL				parseFilterArguments(Parser *parser, FilterNode *filterNode, NSError **error);

#endif

