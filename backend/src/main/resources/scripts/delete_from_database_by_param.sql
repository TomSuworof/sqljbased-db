-- FUNCTION: public.delete_from_database_by_param(text, text, text, text, text)

-- DROP FUNCTION public.delete_from_database_by_param(text, text, text, text, text);

CREATE OR REPLACE FUNCTION public.delete_from_database_by_param(
	dbname text,
	username text,
	password text,
	param_name text,
	param_value text)
    RETURNS void
    LANGUAGE 'plpgsql'

    COST 100
    VOLATILE

AS $BODY$
declare
	conn text;
	conn_name text;
begin

dbname = 'jdbc_' || dbname;

if exists (select 1 from pg_database where datname = dbname) then
	conn_name = md5(random()::text);
	conn = dblink_connect(conn_name, 'dbname=' || dbname || ' user=' || username || ' password=' || password);
    perform dblink_exec(conn_name, 'delete from ' || dbname || '.public.items where ' || param_name || '=' || quote_literal(param_value) || ';');
else
	raise exception 'Database does not exist';

end if;

end
$BODY$;

ALTER FUNCTION public.delete_from_database_by_param(text, text, text, text, text)
    OWNER TO postgres;
