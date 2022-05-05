#include "pch.h"
#include "Case.h"
#include "Node.h"

Case::Case(std::shared_ptr<Node> condition, std::shared_ptr<Node> expression) : condition(condition), expression(expression)
{
}
