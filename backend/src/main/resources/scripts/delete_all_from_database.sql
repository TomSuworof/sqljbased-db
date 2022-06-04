-- FUNCTION: public.delete_all_from_database(text, text, text)

-- DROP FUNCTION public.delete_all_from_database(text, text, text);

CREATE OR REPLACE FUNCTION public.delete_all_from_database(
    dbname text,
    username text,
    password text)
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
        perform dblink_exec(conn_name, 'delete from ' || dbname || '.public.items;');
    else
        raise exception 'Database does not exist';

    end if;

end
$BODY$;

ALTER FUNCTION public.delete_all_from_database(text, text, text)
    OWNER TO postgres;
