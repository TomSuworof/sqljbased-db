-- FUNCTION: public.get_user_by_username(text, text, text, text)

-- DROP FUNCTION public.get_user_by_username(text, text, text, text);

CREATE OR REPLACE FUNCTION public.get_user_by_username(
    username_to_find text,
    username text,
    password text,
    dbname text)
    RETURNS TABLE(found_username text)
    LANGUAGE 'plpgsql'

    COST 100
    VOLATILE
    ROWS 1000

AS $BODY$
declare
    conn text;
    conn_name text;
begin

    dbname = 'jdbc_' || dbname;

    if exists (select 1 from pg_database where datname = dbname) then
        conn_name = md5(random()::text);
        conn = dblink_connect(conn_name, 'dbname=' || dbname || ' user=' || username || ' password=' || password);
        return query select * from dblink(conn_name, 'select usename from pg_catalog.pg_user where usename like ' || quote_literal(username_to_find) || ';') alias(found_username text);
    else
        raise exception 'Database does not exist';
    end if;

end
$BODY$;

ALTER FUNCTION public.get_user_by_username(text, text, text, text)
    OWNER TO postgres;
