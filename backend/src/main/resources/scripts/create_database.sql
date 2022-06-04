-- FUNCTION: public.create_database(text, text, text)

-- DROP FUNCTION public.create_database(text, text, text);

CREATE OR REPLACE FUNCTION public.create_database(
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
    item_script text;
begin

    dbname = 'jdbc_' || dbname;

    if exists (select 1 from pg_database where datname = dbname) then
        raise exception 'Database already exists';
    else
        conn_name = md5(random()::text);
        conn = dblink_connect(conn_name, 'dbname=' || current_database() || ' user=' || username || ' password=' || password);
        perform dblink_exec(conn_name, 'CREATE DATABASE ' || quote_ident(dbname));

        item_script = $$items (
		id integer NOT NULL primary key,
		name text NOT NULL,
		amountAvailable bigint NOT NULL, check(amountAvailable >= 0),
		price integer NOT NULL, check(price >= 0),
		color text NOT NULL,
		refurbished bool NOT NULL
	);$$;

        conn_name = md5(random()::text);
        conn = dblink_connect(conn_name, 'dbname=' || dbname || ' user=' || username || ' password=' || password);
        perform dblink_exec(conn_name, 'CREATE TABLE '|| dbname || '.public.' || item_script);

    end if;

end
$BODY$;

ALTER FUNCTION public.create_database(text, text, text)
    OWNER TO postgres;
