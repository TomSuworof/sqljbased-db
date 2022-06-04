-- FUNCTION: public.get_all_databases()

-- DROP FUNCTION public.get_all_databases();

CREATE OR REPLACE FUNCTION public.get_all_databases(
)
    RETURNS TABLE(dbname name)
    LANGUAGE 'plpgsql'

    COST 100
    VOLATILE
    ROWS 1000

AS $BODY$
begin

    return query select datname from pg_database where datname like 'jdbc_%';

end
$BODY$;

ALTER FUNCTION public.get_all_databases()
    OWNER TO postgres;
