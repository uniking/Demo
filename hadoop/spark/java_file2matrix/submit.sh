 /home/uniking/Eagle/spark-1.3.1-bin-hadoop2.6/bin/spark-submit --name firstspark --class "hello.JavaWordCount" --executor-memory 512m --total-executor-cores 1 --master spark://127.0.0.1:7077  wordcount-0.1.0.jar hdfs://127.0.0.1:8082/tmp/readme
