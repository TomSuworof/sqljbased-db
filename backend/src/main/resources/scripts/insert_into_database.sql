-- FUNCTION: public.insert_into_database(text, text, text, bigint, text, bigint, integer, text, boolean)

-- DROP FUNCTION public.insert_into_database(text, text, text, bigint, text, bigint, integer, text, boolean);

CREATE OR REPLACE FUNCTION public.insert_into_database(
    dbname text,
    username text,
    password text,
    id bigint,
    name text,
    amount bigint,
    price integer,
    color text,
    refurbished boolean)
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
        perform dblink_exec(conn_name, 'insert into ' || dbname || '.public.items values (' || id || ', ' || quote_literal(name) || ', ' || amount || ', ' || price || ', ' || quote_literal(color) || ', ' || refurbished || ');');
    else
        raise exception 'Database does not exist';

    end if;

end
$BODY$;

ALTER FUNCTION public.insert_into_database(text, text, text, bigint, text, bigint, integer, text, boolean)
    OWNER TO postgres;
