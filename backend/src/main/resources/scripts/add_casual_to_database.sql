-- FUNCTION: public.add_casual_to_database(text, text, text, text, text)

-- DROP FUNCTION public.add_casual_to_database(text, text, text, text, text);

CREATE OR REPLACE FUNCTION public.add_casual_to_database(
    username_to_save text,
    password_to_save text,
    username text,
    password text,
    dbname text)
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
        perform dblink_exec(conn_name, 'create user ' || username_to_save || ' password ' || quote_literal(password_to_save) || ';');
        perform dblink_exec(conn_name, 'grant select on items to casual_user;');
        perform dblink_exec(conn_name, 'grant casual_user to ' || username_to_save || ';');
    else
        raise exception 'Database does not exist';
    end if;

end
$BODY$;

ALTER FUNCTION public.add_casual_to_database(text, text, text, text, text)
    OWNER TO postgres;
