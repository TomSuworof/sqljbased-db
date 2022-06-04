-- FUNCTION: public.delete_database(text, text, text)

-- DROP FUNCTION public.delete_database(text, text, text);

CREATE OR REPLACE FUNCTION public.delete_database(
    dbname text,
    username text,
    password text)
    RETURNS integer
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
        conn = dblink_connect(conn_name, 'dbname=' || current_database() || ' user=' || username || ' password=' || password);
        perform dblink_exec(conn_name, 'DROP DATABASE ' || quote_ident(dbname));
        return 0;
    else
        raise exception 'Database does not exist';
        return -1;
    end if;

end
$BODY$;

ALTER FUNCTION public.delete_database(text, text, text)
    OWNER TO postgres;
