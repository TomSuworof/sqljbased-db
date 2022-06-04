-- FUNCTION: public.add_superuser(text, text, text, text)

-- DROP FUNCTION public.add_superuser(text, text, text, text);

CREATE OR REPLACE FUNCTION public.add_superuser(
	username_to_save text,
	password_to_save text,
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

conn_name = md5(random()::text);
conn = dblink_connect(conn_name, 'dbname=' || current_database() || ' user=' || username || ' password=' || password);
perform dblink_exec(conn_name, 'create user ' || username_to_save || ' password ' || quote_literal(password_to_save) || ';');
perform dblink_exec(conn_name, 'ALTER USER ' || username_to_save || ' WITH SUPERUSER;');

end
$BODY$;

ALTER FUNCTION public.add_superuser(text, text, text, text)
    OWNER TO postgres;
