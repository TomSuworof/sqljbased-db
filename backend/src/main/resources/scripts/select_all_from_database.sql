-- FUNCTION: public.select_all_from_database(text, text, text)

-- DROP FUNCTION public.select_all_from_database(text, text, text);

CREATE OR REPLACE FUNCTION public.select_all_from_database(
    dbname text,
    username text,
    password text)
    RETURNS TABLE(id bigint, name text, amountavailable bigint, price integer, color text, refurbished boolean)
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
        return query select * from dblink(conn_name, 'select * from ' || dbname || '.public.items;') alias (id bigint, name text, amountAvailable bigint, price int, color text, refurbished boolean);
    else
        raise exception 'Database does not exist';

    end if;

end
$BODY$;

ALTER FUNCTION public.select_all_from_database(text, text, text)
    OWNER TO postgres;
