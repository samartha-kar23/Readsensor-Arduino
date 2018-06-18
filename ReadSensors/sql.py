import pymysql.cursors

def update(val):
#print("herer")
        #val = 37
    conn = pymysql.connect(host='10.14.88.224', user='root', password='sensor_cloud', db='SENSORS')
    sql = "UPDATE SENSOR SET Data=%s WHERE Type=%s"
        #sql = "UPDATE SENSOR SET Data='33' WHERE Type='Temparature'"
        #sql = "DELETE FROM SENSOR WHERE Type=%s"
    try:
        print(val)
        with conn.cursor() as cursor:
                        #print("\n"+val)
                        #print(flush=True)
            result = cursor.execute(sql,(val,'HUMIDITY'))
            sensor=cursor.fetchall()
            conn.commit()
            print("committed")
    finally:   
            #sleep(10)
        conn.close()
            #print(result)
            #print(sensor)
        return"success"