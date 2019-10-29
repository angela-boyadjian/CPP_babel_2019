/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Connector
*/

#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include "Database.hpp"

namespace babel {
namespace database {

class Connector {
	public:
		Connector();
		~Connector();

		static decltype(auto) get()
		{
			static auto storage = sqlite_orm::make_storage("db.sqlite",
				sqlite_orm::make_table("clients",
					sqlite_orm::make_column("id", &Client::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
					sqlite_orm::make_column("name", &Client::name),
					sqlite_orm::make_column("password", &Client::password)
				),
				sqlite_orm::make_table("friends",
					sqlite_orm::make_column("owner", &Friends::owner),
					sqlite_orm::make_column("target", &Friends::target),
					sqlite_orm::foreign_key(&Friends::owner).references(&Client::id),
					sqlite_orm::foreign_key(&Friends::target).references(&Client::id)
				)
			);
			storage.sync_schema();
			return storage;
		}

	protected:
	private:
};
}
}