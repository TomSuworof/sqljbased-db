-- FUNCTION: public.user_exists_by_username(text, text, text, text)

-- DROP FUNCTION public.user_exists_by_username(text, text, text, text);

CREATE OR REPLACE FUNCTION public.user_exists_by_username(
    username_to_find text,
    username text,
    password text,
    dbname text)
    RETURNS TABLE(user_exists boolean)
    LANGUAGE 'plpgsql'

    COST 100
    VOLATILE
    ROWS 1000

AS $BODY$
declare
    username_found text;
begin

    select found_username into username_found from get_user_by_username(username_to_find, username, password, dbname);

    return query select found as user_exists;

end
$BODY$;

ALTER FUNCTION public.user_exists_by_username(text, text, text, text)
    OWNER TO postgres;
