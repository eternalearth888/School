#!/usr/bin/env ruby
#
# Maria Deslis
# csci403 - Bakos - spring 2013
#

require 'redis'

redis = Redis.new(:host => "pub-redis-13059.us-west-1.1.azure.garantiadata.com", :port => 13059, :password => "wuwnosql403")

puts "1: SET server:name \"test\""
puts redis.SET("test", "Hello World")

puts "2: GET server:name"
puts redis.GET("test")

puts "3: SET connections 10"
puts redis.SET("test", 10)

puts "4: INCR connections"
puts redis.INCR("test")

puts "5: DEL connections"
puts redis.del("test")

puts "6: RPUSH senshi \"Saturn\""
puts redis.RPUSH("senshi", "Saturn")

puts "7: LPUSH senshi \"Pluto\""
puts redis.LPUSH("senshi", "Pluto")

puts "8: LRANGE senshi 0 -1"
puts redis.LRANGE("senshi", 0, -1)

puts "9: LLEN senshi"
puts redis.LLEN("senshi")

puts "10: LPOP senshi"
puts redis.LPOP("senshi")

puts "11: RPOP senshi"
puts redis.RPOP("senshi")

puts "12: DEL senshi"
puts redis.del("senshi")

puts "13: SADD designers \"CHANEL\""
puts redis.SADD("designers", "CHANEL")
puts "SADD designers \"Yves Saint Laurent\""
puts redis.SADD("designers", "Yves Saint Laurent")
puts "SADD designers \"Gucci\""
puts redis.SADD("designers", "Gucci")

puts "14: SREM designers \"Gucci\""
puts redis.srem("designers", "Gucci")

puts "15: SISMEMBER designers \"CHANEL\""
puts redis.SISMEMBER("designers", "CHANEL")
puts "SISMEMBER designers \"Gucci\""
puts redis.SISMEMBER("designers", "Gucci")

puts "16: SMEMBERS designers"
puts redis.SMEMBERS("designers")

puts "SADD artists \"Picasso\""
puts redis.SADD("artists", "Picasso")

puts "17: SUNION designers artists"
puts redis.SUNION("designers", "artists")

puts "18: ZADD howmanytoday 3 \"Heineken\""
puts redis.ZADD("howmanytoday", 3, "Heineken")
puts "ZADD howmanytoday 1 \"ABSOLUT Mandarin\""
puts redis.ZADD("howmanytoday", 1, "ABSOLUT Mandarin")
puts "ZADD howmanytoday 5 \"Green Tea\""
puts redis.ZADD("howmanytoday", 5, "Green Tea")

puts "19: ZRANGE howmanytoday 0 -1"
puts redis.ZRANGE("howmanytoday", 0 , -1)

puts "20: ZREM howmanytoday 0 -1"
puts redis.ZREM("howmanytoday", 0, -1)