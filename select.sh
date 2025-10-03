SPOOL_FILE=${LOG_DIR}/${LOG_FILE_NAME}.spool 
ORACLE_BIN="C:\\app\\oracle_account\\product\\12.1.0\\somefolder\\bin"
SQLPLUS_OUTPUT=`sqlplus -s  "$SFDC_WE_CORE" <<EOF 
        SET HEAD OFF
        SET AUTOPRINT OFF
        SET TERMOUT OFF
        SET SERVEROUTPUT ON

        SPOOL  ${SPOOL_FILE} 

        WHENEVER SQLERROR EXIT SQL.SQLCODE
        DECLARE 

        BEGIN
           foooo 
        --rollback; 
        END;
    /
    EOF` 

RC=$?

if [[ $RC != 0 ]] ; then

    echo " RDBMS exit code : $RC  "     | tee -a ${LOG_FILE}
    cat ${SPOOL_FILE}                   | tee -a ${LOG_FILE}

    cat ${LOG_FILE} | mail -s "Script ${INIT_EXE} failed on $SFDC_ENV" $SUPPORT_LIST

    exit 3

fi
