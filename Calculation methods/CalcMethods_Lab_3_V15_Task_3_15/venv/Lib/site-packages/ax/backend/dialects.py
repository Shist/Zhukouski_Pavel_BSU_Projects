"""
All SQL queries are generated throw this module.
sea init_dialects
"""
import sys
import sqlite3
import datetime
import uuid
import re
import json
from loguru import logger
from backend.model import AxForm
import backend.misc as ax_misc
import backend.model as ax_model

this = sys.modules[__name__]
dialect_name = None
dialect = None

default_grid_query = '''SELECT {ax.db_fields}
    FROM "{ax.db_table}";'''

class PorstgreDialect(object):
    """SQL query for Postgre SQL database"""

    name = 'postgre'
    version = None


    async def get_tom_sql(self, form_db_name, form_name, tom_label, fields):
        """    '{{name}} {{surname}}' -> 'Mikhail Marenov'
        Each form have 1toM label option. It could be '{{name}} {{surname}}'
        This function custructs SELECT statement string that will return
        'Mikhail Marenov' string as result. Where 'Mikhail' is from 'name'
        column and 'Marenov' from 'surname' column

        Args:
            form_db_name (str): db_name of form. Same as table name.
            form_name (str): Name of form. Used to replace {{ax_form_name}}
            tom_label (str): Tom label option of AxForm
            fields (List(AxField)): List of all AxFields of current form

        Returns:
            str: SQL statement to be placed in SELECT statement
        """
        tags = re.findall("{{(.*?)}}", tom_label)
        true_tags = []
        for field in fields:
            if field.db_name in tags:
                true_tags.append('"' + field.db_name + '"')

        if "guid" in tags:
            true_tags.append("guid")

        tom_label_modified = tom_label.replace("{{ax_form_name}}", form_name)
        tom_label_modified = tom_label_modified.replace(
            "{{ax_db_name}}", form_db_name)

        texts = re.split('{{.*?}}', tom_label_modified)
        true_texts = []
        for text in texts:
            if text != "":
                true_texts.append("'" + text + "'")
            else:
                true_texts.append(text)

        if not true_tags:
            return f'"guid"'
            # return f"{true_texts[0]}"

        zip_result = zip(true_texts, true_tags)
        tom_view_arr = [x for item in zip_result for x in item]
        tom_view_arr_clean = [name for name in tom_view_arr if name != ""]

        sql_tom_name = " || ".join(tom_view_arr_clean)
        return sql_tom_name


    async def get_type(self, type_name):
        """Get dialect specific type"""
        postgre_types = {
            'TEXT': 'TEXT',
            'VARCHAR(255)': 'VARCHAR(255)',
            'INT': 'INT',
            'DECIMAL(65,2)': 'DECIMAL(65,2)',
            'BOOL': 'BOOLEAN',
            'GUID': 'UUID',
            'JSON': 'JSON',
            'TIMESTAMP': 'TIMESTAMP',
            'BLOB': 'bytea'
        }
        return postgre_types[type_name]

    async def get_select_sql(self, type_name, db_name):
        """Some value types need a transformation inside SQL Select statement.

        Args:
            type_name (str): value of AxField.AxFieldType.value_type, like INT
            db_name (str): AxField.db_name, the column name of table

        Returns:
            str: SQL statement to be placed in select section
                SET <db_name>=<this function>
        """
        ret_val = None
        if "BLOB" in type_name:
            ret_val = f'octet_length("{db_name}") as "{db_name}"'
        elif "TIMESTAMP" in type_name:
            ret_val = f'cast(extract(epoch from "{db_name}") as integer) as "{db_name}"'
            # ret_val = f'date_part("{db_name}"::text, CURRENT_TIMESTAMP)::integer'
        else:
            ret_val = f'"{db_name}"'
        return ret_val


    async def get_value_sql(self, type_name, db_name):
        """Some value types need a cast inside SQL.
        Like [UPDATE <table> SET <field>=<this function>]
        It uses param names same as db_name, like :surname

        Args:
            type_name (str): value of AxFieldType.value_type, like INT
            db_name (str): AxField.db_name, the column name of table

        Returns:
            str: SQL statement to be placed in value section
                SET <db_name>=<this function>
        """
        ret_val = None
        if "TIMESTAMP" in type_name:
            ret_val = f"to_timestamp(:{db_name})"
        else:
            ret_val = f":{db_name}"
        return ret_val


    async def get_value_param(self, type_name, value=None):
        """ Some value types needs to convert field value before submiting
        to SQL.

        Args:
            type_name (str): value of AxFieldType.value_type, like INT
            value (object, optional): Value of field. Defaults to None.

        Returns:
            object: initial value of converted value if needed by field type
        """
        ret_param = None
        if "DECIMAL" in type_name:
            ret_param = float(str(value).replace(",", ".")) if value else None
        elif "INT" in type_name:
            ret_param = int(value) if value else None
        elif "JSON" in type_name:
            ret_param = json.dumps(value) if value else None
        elif "GUID" in type_name:
            ret_param = str(value) if value else None
        elif "BOOL" in type_name:
            if not value or value == 0:
                return False
            return True
        else:
            ret_param = value if value else None
        return ret_param


    async def get_value(self, type_name, value):
        """ SELECT cat return different types for diferent dialects
        This method makes returning value same.
            Sqllite returns JSON as string
            Postgre returns JSON as dict  """
        ret_value = value
        if "JSON" in type_name:
            ret_value = json.dumps(value) if value else None
        return ret_value



    async def conver_for_graphql(self, value):
        """ Convert SQL field value to GraphQL value """
        ret_value = value
        if isinstance(value, datetime.datetime):
            try:
                ret_value = int(value.timestamp()) if value else None
            except Exception:
                try:
                    ret_value = int(value.timestamp()/1000) if value else None
                except Exception:
                    return None
        return ret_value


    def custom_query(self, sql, variables=None):
        """ Executes any SQL. Used in action python code.
        This method is SYNC, leave it so

        Args:
            db_session: SqlAlchemy session
            sql (str): Any sql that needs to be executed
            variables (Dict): Arguments used in sql query

        Returns:
            List(Dict(column_name: value)): result of SQL query
        """

        with ax_model.scoped_session("SQL - custom_query") as db_session:
            res = db_session.execute(sql, variables)
            db_session.commit()
            if res and res.returns_rows:
                return res.fetchall()
            return res


    async def select_all(self, db_session, ax_form, quicksearch=None,
                         guids=None):
        """ Select * from table

        Args:
            db_session: SqlAlchemy session
            ax_form (AxForm): Current AxForm
            quicksearch (str, optional): Search string from AxGrid.vue
            guids (str, optional): JSON containing list of guids, that must be
                selected. Used in 1tom fields. Where you need to display only
                selected guids.

        Returns:
            List(Dict): Result of SqlAlchemy query. List of rows
        """
        try:
            sql_params = {}

            tom_name = await self.get_tom_sql(
                form_db_name=ax_form.db_name,
                form_name=ax_form.name,
                tom_label=ax_form.tom_label,
                fields=ax_form.db_fields)

            fields_sql = ", ".join(
                '"' + field.db_name + '"' for field in ax_form.db_fields)

            # If no fields -> no , needed
            if fields_sql:
                fields_sql = "," + fields_sql

            quicksearch_sql = ''
            if quicksearch:
                sql_params['quicksearch'] = quicksearch
                quicksearch_sql = (
                    f"AND CAST({tom_name} AS VARCHAR) ILIKE ('%' || :quicksearch || '%') "
                )

            guids_sql = ''
            if guids:
                guids_array = json.loads(guids)['items']
                if isinstance(guids_array, str):
                    guids_array = json.loads(guids_array)

                guids_string = ''
                if guids_array:
                    checked_guids = []
                    for check_guid in guids_array:
                        try:
                            uuid.UUID(check_guid)
                            checked_guids.append(check_guid)
                        except Exception:
                            pass
                            # logger.exception(
                            #     f"Error in guids argument. Cant parse json")
                            # raise

                    guids_string = ", ".join(
                        "'" + item + "'" for item in checked_guids)
                    guids_sql = f"OR guid IN ({guids_string})"
                    if not quicksearch_sql:
                        guids_sql = f"AND guid IN ({guids_string})"
            sql = (
                f'SELECT guid, "axState" {fields_sql}'
                f', {tom_name} as "axLabel" FROM "{ax_form.db_name}"'
                f' WHERE (1=1 {quicksearch_sql}) {guids_sql}'
            )

            result = db_session.execute(sql, sql_params).fetchall()
            # Some values must be converted before returning to GQL
            # Example - we need to do json.dumps before returning JSON field
            clean_result = []
            for row in result:
                clean_row = {
                    "guid": row["guid"],
                    "axState": row["axState"],
                    "axLabel": row['axLabel']
                }
                for field in ax_form.db_fields:
                    clean_row[field.db_name] = await self.get_value(
                        field.field_type.value_type, row[field.db_name])
                clean_result.append(clean_row)

            return clean_result
            # names = [row[0] for row in result]
        except Exception:
            if not sql:
                sql = 'NONE'
            logger.exception(
                f"Error executing SQL - select_all - {sql}")
            raise




    async def select_custom_query(
            self, db_session, ax_form, sql, arguments=None):
        """ Custom select query that used in AxGrid and grid_schema

        Args:
            db_session: SqlAlchemy session
            ax_form (AxForm): Current AxForm
            sql (str): Query that must be executed
            arguments (Dict): SQL query arguments

        Returns:
            List(Dict): Result of SqlAlchemy query. List of rows
        """
        try:
            if not sql:
                return None

            final_sql = sql

            if '{ax.db_fields}' in final_sql:
                db_fields_sql = ", ".join(
                    '"' + field.db_name + '"' for field in ax_form.db_fields)

                if db_fields_sql:
                    db_fields_sql = ", " + db_fields_sql

                tom_name = await self.get_tom_sql(
                    form_db_name=ax_form.db_name,
                    form_name=ax_form.name,
                    tom_label=ax_form.tom_label,
                    fields=ax_form.db_fields)

                fields_sql = (
                    f'"guid", "axState" {db_fields_sql}, {tom_name} as "axLabel"')
                final_sql = sql.replace('{ax.db_fields}', fields_sql)
                final_sql = final_sql.replace('{ax.tom_label}', tom_name)
                final_sql = final_sql.replace('{ax.db_table}', ax_form.db_name)

            result = db_session.execute(final_sql, arguments).fetchall()
            # Some values must be converted before returning to GQL
            # Example - we need to do json.dumps before returning JSON field
            clean_result = []
            for row in result:
                clean_row = {}
                for must_field in ['guid', 'axState', 'axLabel']:
                    if must_field in row:
                        clean_row[must_field] = row[must_field]
                    else:
                        clean_row[must_field] = None

                for field in ax_form.db_fields:
                    if field.db_name in row:
                        clean_row[field.db_name] = await self.get_value(
                            field.field_type.value_type, row[field.db_name])
                clean_result.append(clean_row)

            return clean_result
            # names = [row[0] for row in result]
        except Exception:
            logger.exception(
                f"Error executing SQL - select_custom_query - {sql}")
            raise




    async def select_one(self, db_session, form, fields_list, row_guid):
        """Select fields from table for one row

        Args:
            db_session: SqlAlchemy session
            form (AxForm): Current form
            fields_list (List(AxField)): Fields that must be selected.
            row_guid (str): String of row guid
            num_fields (List(AxField)): AxNum fields. If not empy, row will
                be searched by guid and every AxNum

        Returns:
            List(Dict(column_name: value)): result of SQL query
        """
        try:

            if not row_guid or row_guid == 'None':
                return None

            form_db_name = form.db_name
            num_fields = []
            for field in form.db_fields:
                if field.field_type.tag == 'AxNum':
                    num_fields.append(field)
            fields_string = '"guid", "axState"'
            for field in fields_list:
                field_db_name = field.db_name
                if field.field_type.is_virtual:
                    field_db_name = field.field_type.virtual_source
                field_name = await self.get_select_sql(
                    field.field_type.value_type, field_db_name)
                fields_string += f', {field_name}'

            sql = None
            query_params = None

            if ax_misc.string_is_guid(str(row_guid)):
                sql = (f'SELECT {fields_string} '
                       f'FROM "{form_db_name}" '
                       f'WHERE guid=:row_guid')
                query_params = {"row_guid": str(row_guid)}
            elif num_fields:
                num_where = []
                for num_field in num_fields:
                    num_where.append(f'"{num_field.db_name}"=:ax_num')
                num_where_sql = " OR ".join(num_where)

                sql = (f'SELECT {fields_string} '
                       f'FROM "{form_db_name}" '
                       f'WHERE {num_where_sql}')
                query_params = {"ax_num": str(row_guid)}

            result = db_session.execute(sql, query_params).fetchall()
            return result

        except Exception:
            logger.exception(f"Error executing SQL - select_one - {sql}")
            raise



    async def select_field(self, db_session, form_db_name, field_db_name,
                           row_guid):
        """Gets value of single field from SQL. Used in file viewer.
        See routes.py

        Args:
            db_session: SqlAlchemy session
            form_db_name (str): AxForm.db_name - table name of current form
            fields_db_name (str): Db name of field
            row_guid (str): String of row guid

        Returns:
            List(Dict(column_name: value)): result of SQL query
        """
        try:
            sql = (f"SELECT \"{field_db_name}\" "
                   f"FROM \"{form_db_name}\" "
                   f"WHERE guid=:row_guid"
                   )
            params = {
                "row_guid": row_guid
            }
            result = db_session.execute(sql, params).fetchall()
            return result[0][field_db_name] if result else None
        except Exception:
            logger.exception(
                f"Error executing SQL - select_field {form_db_name}")
            raise


    async def insert(self, db_session, form, to_state_name, new_guid):
        """ Insert row into database and set state with AxForm field values

        Args:
            db_session: SqlAlchemy session
            form (AxForm): Current form with filled field values.
            to_state_name (str): Name of form state that must be set
            new_guid (str): Guid that must be used to create record.

        Returns:
            str: Guid of created row
        """
        try:
            fields_db_names = []
            query_params = {
                "ax_state": to_state_name,
                "row_guid": str(new_guid)
            }

            value_strings = []
            for field in form.fields:
                if field.needs_sql_update or field.force_sql_update:
                    fields_db_names.append(f'"{field.db_name}"')
                    value_str = await self.get_value_sql(
                        type_name=field.field_type.value_type,
                        db_name=field.db_name)
                    value_strings.append(value_str)
                    query_params[field.db_name] = await self.get_value_param(
                        type_name=field.field_type.value_type,
                        value=field.value)

            column_sql = ", ".join(fields_db_names)
            if column_sql:
                column_sql = ', ' + column_sql

            values_sql = ", ".join(value_strings)
            if values_sql:
                values_sql = ',' + values_sql

            sql = (
                f'INSERT INTO "{form.db_name}" '
                f'("guid", "axState" {column_sql}) '
                f"VALUES (:row_guid, :ax_state {values_sql});"
            )
            db_session.execute(sql, query_params)
            return new_guid
        except Exception:
            logger.exception('Error executing SQL - insert')
            raise


    async def update(self, db_session, form, to_state_name, row_guid):
        """Update database row based of AxForm fields values

        Args:
            db_session: SqlAlchemy session
            form (AxForm): Current form with filled field values.
            to_state_name (str): Name of form state that must be set
            row_guid (str): Guid of updated row

        Returns:
            SqlAlchemy result: Contains nothing. Not used.
        """
        try:
            value_strings = []
            query_params = {
                "ax_state": to_state_name,
                "row_guid": row_guid
            }
            for field in form.db_fields:
                if field.needs_sql_update or field.force_sql_update:
                    current_valu_str = await self.get_value_sql(
                        type_name=field.field_type.value_type,
                        db_name=field.db_name
                    )
                    value_strings.append(
                        f"\"{field.db_name}\"={current_valu_str}")
                    query_params[field.db_name] = await self.get_value_param(
                        type_name=field.field_type.value_type,
                        value=field.value
                    )

            values_sql = ", ".join(value_strings)
            if values_sql:
                values_sql = ", " + values_sql
            sql = (
                f"UPDATE \"{form.db_name}\" "
                f"SET \"axState\"=:ax_state {values_sql} "
                f"WHERE guid=:row_guid "
            )
            return db_session.execute(sql, query_params)

        except Exception:
            logger.exception('Error executing SQL - update')
            raise


    async def delete(self, db_session, form, row_guid):
        """ Delete row of table of form"""
        try:
            sql = (
                f"DELETE FROM \"{form.db_name}\" WHERE guid='{row_guid}' "
            )
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - delete')
            raise


    async def create_data_table(self, db_session, db_name):
        """Create table with system columns"""
        try:
            sql = f"""CREATE TABLE \"{db_name}\" (
                guid UUID PRIMARY KEY,
                \"axState\" VARCHAR NOT NULL
            );"""
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - create_data_table')
            raise

    async def rename_table(self, db_session, old, new):
        """Rename table"""
        try:
            sql = f'ALTER TABLE "{old}" RENAME TO "{new}";'
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - rename_table')
            raise


    async def drop_table(self, db_session, db_name):
        """Drop table"""
        try:
            sql = f'DROP TABLE "{db_name}";'
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - drop_table')
            raise


    async def add_column(self, db_session, table, db_name, type_name):
        """Add column"""
        try:
            dialect_type = await self.get_type(type_name=type_name)
            sql = f'ALTER TABLE "{table}" ADD COLUMN "{db_name}" {dialect_type}'
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - add_column')
            raise

    async def rename_column(self, db_session, table, old_name, new_name,
                            type_name) -> None:
        """Rename column"""
        try:
            del type_name
            sql = (
                f'ALTER TABLE "{table}"'
                f' RENAME COLUMN "{old_name}" TO "{new_name}";'
            )
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - rename_column')
            raise

    async def drop_column(self, db_session, table, column) -> None:
        """ Drop column """
        try:
            sql = f'ALTER TABLE "{table}" DROP COLUMN "{column}";'
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - drop_column')
            raise

    async def select_group_users(self, db_session, group_guid):
        """ Select of users of group """
        try:
            sql = """
                SELECT us.guid, us.short_name
                FROM "_ax_group2user" g2u, "_ax_users" us
                WHERE g2u.user_guid = us.guid AND g2u.group_guid=:group_guid;            
            """
            query_params = {
                "group_guid": group_guid
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_group_users')
            raise


    async def select_role_users(self, db_session, role_guid):
        """ Select of users of group """
        try:
            sql = """
                SELECT us.guid, us.short_name
                FROM "_ax_role2user" r2u, "_ax_users" us
                WHERE r2u.user_guid = us.guid AND r2u.role_guid=:role_guid;            
            """
            query_params = {
                "role_guid": role_guid
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_role_users')
            raise


    async def select_page_users(self, db_session, page_guid):
        """ Select of users that can view page """
        try:
            sql = """
                SELECT us.guid, us.short_name
                FROM "_ax_page2user" p2u, "_ax_users" us
                WHERE p2u.user_guid = us.guid AND p2u.page_guid=:page_guid;            
            """
            query_params = {
                "page_guid": uuid.UUID(page_guid)
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_page_users')
            raise


    async def select_to1_children(
            self,
            db_session,
            child_form_db_name,
            child_field_db_name,
            parent_row_guid):
        """ Used in Ax1to1Children. Selects all 1to1 references to parent row
            """
        try:
            sql = f"""
                SELECT guid FROM "{child_form_db_name}"
                WHERE CAST("{child_field_db_name}" AS VARCHAR) = :parent_row_guid
            """
            query_params = {
                "parent_row_guid": parent_row_guid
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_to1_children')
            raise



class SqliteDialect(PorstgreDialect):
    """SQL query for Sqlite database"""
    name = 'sqlite'
    version = None

    async def get_type(self, type_name) -> str:
        """Get dialect specific type"""
        sqlite_types = {
            'TEXT': 'TEXT',
            'VARCHAR(255)': 'TEXT',
            'INT': 'INTEGER',
            'DECIMAL(65,2)': 'REAL',
            'BOOL': 'NUMERIC',
            'GUID': 'TEXT',
            'TIMESTAMP': 'INTEGER',
            'BLOB': 'BLOB',
            'JSON': 'TEXT'
        }
        return sqlite_types[type_name]

    async def get_select_sql(self, type_name, db_name):
        """Some value types need a transformation inside SQL Select statement.

        Args:
            type_name (str): value of AxField.AxFieldType.value_type, like INT
            db_name (str): AxField.db_name, the column name of table

        Returns:
            str: SQL statement to be placed in select section
                SET <db_name>=<this function>
        """
        ret_val = None
        if "BLOB" in type_name:
            ret_val = f"LENGTH({db_name}) as \"{db_name}\""
        else:
            ret_val = f'"{db_name}"'
        return ret_val

    async def get_value_sql(self, type_name, db_name):
        """Some value types need a cast inside SQL.
        Like [UPDATE <table> SET <field>=<this function>]
        It uses param names same as db_name, like :surname

        Args:
            type_name (str): value of AxFieldType.value_type, like INT
            db_name (str): AxField.db_name, the column name of table

        Returns:
            str: SQL statement to be placed in value section
                SET <db_name>=<this function>
        """
        ret_val = None
        if "TIMESTAMP" in type_name:
            ret_val = f"CAST(:{db_name} AS INTEGER)"
        elif "DECIMAL" in type_name:
            ret_val = f"CAST(:{db_name} AS REAL)"
        else:
            ret_val = f":{db_name}"
        return ret_val

    async def get_value_param(self, type_name, value=None):
        """ Some value types needs to convert field value before submiting
        to SQL.

        Args:
            type_name (str): value of AxFieldType.value_type, like INT
            value (object, optional): Value of field. Defaults to None.

        Returns:
            object: initial value of converted value if needed by field type
        """
        ret_param = None
        if "DECIMAL" in type_name:
            ret_param = str(value).replace(",", ".") if value else None
        elif "GUID" in type_name:
            ret_param = str(value)
        elif "JSON" in type_name:
            if not value:
                return None
            obj_value = value
            if isinstance(value, str):
                try:
                    obj_value = json.loads(value)
                except Exception:
                    obj_value = None
                    logger.error(
                        f'Error in dialect -> get_value_param -> cant json.loads value')
            ret_param = json.dumps(obj_value) if obj_value else None
        else:
            ret_param = value if value else None
        return ret_param



    async def get_value(self, type_name, value):
        """ SELECT cat return different types for diferent dialects
        This method makes returning value same.
            Sqllite returns JSON as string
            Postgre returns JSON as dict  """
        ret_value = value
        return ret_value


    async def select_all(self, db_session, ax_form, quicksearch=None,
                         guids=None):
        """ Select * from table

        Args:
            db_session: SqlAlchemy session
            ax_form (AxForm): Current AxForm
            quicksearch (str, optional): Search string from AxGrid.vue
            guids (str, optional): JSON containing list of guids, that must be
                selected. Used in 1tom fields. Where you need to display only
                selected guids.

        Returns:
            List(Dict): Result of SqlAlchemy query. List of rows
        """
        try:
            sql_params = {}

            tom_name = await self.get_tom_sql(
                form_db_name=ax_form.db_name,
                form_name=ax_form.name,
                tom_label=ax_form.tom_label,
                fields=ax_form.db_fields)

            fields_sql = ", ".join(
                '"' + field.db_name + '"' for field in ax_form.db_fields)

            # If no fields -> no , needed
            if fields_sql:
                fields_sql = "," + fields_sql

            quicksearch_sql = ''
            if quicksearch:
                sql_params['quicksearch'] = quicksearch
                quicksearch_sql = (
                    f"AND CAST({tom_name} AS VARCHAR) LIKE ('%' || :quicksearch || '%') "
                )

            guids_sql = ''
            if guids:
                guids_array = json.loads(guids)['items']
                if isinstance(guids_array, str):
                    guids_array = json.loads(guids_array)

                guids_string = ''
                if guids_array:
                    checked_guids = []
                    for check_guid in guids_array:
                        try:
                            uuid.UUID(check_guid)
                            checked_guids.append(check_guid)
                        except Exception:
                            pass
                            # logger.exception(
                            #     f"Error in guids argument. Cant parse json")
                            # raise

                    guids_string = ", ".join(
                        "'" + item + "'" for item in checked_guids)
                    guids_sql = f"OR guid IN ({guids_string})"
                    if not quicksearch_sql:
                        guids_sql = f"AND guid IN ({guids_string})"
            sql = (
                f'SELECT guid, "axState" {fields_sql}'
                f', {tom_name} as "axLabel" FROM "{ax_form.db_name}"'
                f' WHERE (1=1 {quicksearch_sql}) {guids_sql}'
            )

            result = db_session.execute(sql, sql_params).fetchall()
            # Some values must be converted before returning to GQL
            # Example - we need to do json.dumps before returning JSON field
            clean_result = []
            for row in result:
                clean_row = {
                    "guid": row["guid"],
                    "axState": row["axState"],
                    "axLabel": row['axLabel']
                }
                for field in ax_form.db_fields:
                    clean_row[field.db_name] = await self.get_value(
                        field.field_type.value_type, row[field.db_name])
                clean_result.append(clean_row)

            return clean_result
            # names = [row[0] for row in result]
        except Exception:
            if not sql:
                sql = 'NONE'
            logger.exception(
                f"Error executing SQL - select_all - {sql}")
            raise



    async def create_data_table(self, db_session, db_name: str) -> None:
        """Create table with system columns"""
        try:
            sql = f"""CREATE TABLE {db_name} (
                guid VARCHAR PRIMARY KEY,
                axState VARCHAR NOT NULL
            );"""
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - create_data_table')
            raise

    async def rename_column(
            self, db_session, table, old_name, new_name, type_name) -> None:
        """Sqlite allows rename of column only from version 3.25.0.
        We have to reacreate table and copy data"""
        try:
            del type_name
            ax_form = db_session.query(AxForm).filter(
                AxForm.db_name == table
            ).first()

            drop_tmp = f"DROP TABLE IF EXISTS _ax_tmp"

            create_tmp = (
                f"CREATE TABLE _ax_tmp ("
                f"guid VARCHAR, "
                f"axState VARCHAR"
            )
            for field in ax_form.db_fields:
                db_name = field.db_name if (
                    field.db_name != old_name) else new_name
                db_type = await self.get_type(field.field_type.value_type)
                create_tmp += f", {db_name}  {db_type}"

            create_tmp += ');'

            copy_data = 'INSERT INTO _ax_tmp SELECT guid, axState'
            for field in ax_form.db_fields:
                copy_data += f", {field.db_name}"
            copy_data += f" FROM {ax_form.db_name};"

            drop_old = f"DROP TABLE {ax_form.db_name};"

            rename_tmp = f'ALTER TABLE _ax_tmp RENAME TO {ax_form.db_name};'

            db_session.execute(drop_tmp)
            db_session.execute(create_tmp)
            db_session.execute(copy_data)
            db_session.execute(drop_old)
            db_session.execute(rename_tmp)

        except Exception:
            logger.exception('Error executing SQL - rename_column')
            raise

    async def drop_column(self, db_session, table, column) -> None:
        """Sqlite does not allows to drop columns.
        We have to reacreate table and copy data"""
        try:
            ax_form = db_session.query(AxForm).filter(
                AxForm.db_name == table
            ).first()

            drop_tmp = f"DROP TABLE IF EXISTS _ax_tmp"
            create_tmp = (
                f"CREATE TABLE _ax_tmp ("
                f"guid VARCHAR, "
                f"axState VARCHAR"
            )
            for field in ax_form.db_fields:
                db_type = await self.get_type(field.field_type.value_type)
                if field.db_name != column:
                    create_tmp += f", {field.db_name}  {db_type}"
            create_tmp += ');'

            copy_data = 'INSERT INTO _ax_tmp SELECT guid, axState'
            for field in ax_form.db_fields:
                if field.db_name != column:
                    copy_data += f", {field.db_name}"
            copy_data += f" FROM {ax_form.db_name};"
            drop_old = f"DROP TABLE {ax_form.db_name};"
            rename_tmp = f'ALTER TABLE _ax_tmp RENAME TO {ax_form.db_name};'

            db_session.execute(drop_tmp)
            db_session.execute(create_tmp)
            db_session.execute(copy_data)
            db_session.execute(drop_old)
            db_session.execute(rename_tmp)

            return True
        except Exception:
            logger.exception('Error executing SQL - drop_column')
            raise


    async def select_group_users(self, db_session, group_guid):
        """ Select of users of group """
        try:
            sql = """
                SELECT us.guid, us.short_name
                FROM "_ax_group2user" g2u, "_ax_users" us
                WHERE g2u.user_guid = us.guid AND g2u.group_guid=:group_guid;            
            """
            query_params = {
                "group_guid": str(group_guid)
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_group_users')
            raise


    async def select_role_users(self, db_session, role_guid):
        """ Select of users of group """
        try:
            sql = """
                SELECT us.guid, us.short_name
                FROM "_ax_role2user" r2u, "_ax_users" us
                WHERE r2u.user_guid = us.guid AND r2u.role_guid=:role_guid;            
            """
            query_params = {
                "role_guid": str(role_guid)
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_role_users')
            raise


    async def select_page_users(self, db_session, page_guid):
        """ Select of users that can view page """
        try:
            sql = """
                SELECT us.guid, us.short_name
                FROM "_ax_page2user" p2u, "_ax_users" us
                WHERE p2u.user_guid = us.guid AND p2u.page_guid=:page_guid;            
            """
            query_params = {
                "page_guid": str(uuid.UUID(page_guid))
            }
            result = db_session.execute(sql, query_params).fetchall()
            return result
        except Exception:
            logger.exception('Error executing SQL - select_page_users')
            raise



class MysqlDialect(object):
    """SQL query for Mysql database"""

    name = 'mysql'
    version = None

    async def get_type(self, type_name):
        """Get dialect specific type"""
        mysql_types = {
            'TEXT': 'TEXT',
            'VARCHAR(255)': 'VARCHAR(255)',
            'INT': 'INT',
            'DECIMAL(65,2)': 'DECIMAL(65,2)',
            'BOOL': 'BOOL',
            'GUID': 'CHAR(32)',
            'JSON': 'TEXT',
            'TIMESTAMP': 'TIMESTAMP',
            'BLOB': 'BLOB'
        }
        return mysql_types[type_name]


    async def get_value(self, type_name, value):
        """ SELECT cat return different types for diferent dialects
        This method makes returning value same """
        del type_name
        ret_value = value
        return ret_value

    async def create_data_table(self, db_session, db_name) -> None:
        """Create table with system columns"""
        try:
            sql = f"""CREATE TABLE {db_name} (
                guid VARCHAR(64) PRIMARY KEY,
                axState VARCHAR(255) NOT NULL
            );"""
            db_session.execute(sql)
        except Exception:
            logger.exception('Error executing SQL - create_data_table')
            raise


def init_dialects(_dialect_name: str) -> None:
    """Initiate sql queries for right dialect"""
    try:
        this.dialect_name = _dialect_name
        if _dialect_name == 'sqlite':
            this.dialect = SqliteDialect()
            this.dialect.version = sqlite3.sqlite_version
        elif _dialect_name == 'postgre':
            this.dialect = PorstgreDialect()
        elif _dialect_name == 'mysql':
            this.dialect = MysqlDialect()
        else:
            raise Exception('Unknown dialect = ' + _dialect_name)

        logger.debug("Dialect initialised -> {dialect} -> {version}",
                     dialect=this.dialect.name, version=this.dialect.version)

    except Exception:
        logger.exception('Error initiating dialects')
        raise
