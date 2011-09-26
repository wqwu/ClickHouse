#pragma once

#include <DB/AggregateFunctions/IAggregateFunction.h>


namespace DB
{

/** Интерфейс для агрегатных функций, принимающих одно значение. Это почти все агрегатные функции.
  */
class IUnaryAggregateFunction : public IAggregateFunction
{
public:
	void setArguments(const DataTypes & arguments)
	{
		if (arguments.size() != 1)
			throw Exception("Passed " + Poco::NumberFormatter::format(arguments.size()) + " arguments to unary aggregate function " + getName(),
				ErrorCodes::NUMBER_OF_ARGUMENTS_DOESNT_MATCH);
		setArgument(arguments[0]);
	}

	virtual void setArgument(const DataTypePtr & argument) = 0;

	/// Добавить значение.
	void add(const Row & row)
	{
		addOne(row[0]);
	}

	virtual void addOne(const Field & value) = 0;
};

}
