-- FUNCTION: public.count_all_from_database(text, text, text)

-- DROP FUNCTION public.count_all_from_database(text, text, text);

CREATE OR REPLACE FUNCTION public.count_all_from_database(
    dbname text,
    username text,
    password text)
    RETURNS TABLE(count bigint)
    LANGUAGE 'plpgsql'

    COST 100
    VOLATILE
    ROWS 1000

AS $BODY$
declare
begin

    return query select count(*) as count from select_all_from_database(dbname, username, password);

end
$BODY$;

ALTER FUNCTION public.count_all_from_database(text, text, text)
    OWNER TO postgres;
