#!/usr/bin/env ruby

require 'rubygems'
require 'active_record'
require 'logger'

#
# Configuration
#
ActiveRecord::Base.logger = Logger.new(STDOUT) # Comment this line to turn off log output
ActiveRecord::Base.establish_connection(
  :host => 'csci403.c99q7trvwetr.us-west-2.rds.amazonaws.com',
  :username => 'mdeslis',
  :password => 'Hitsuzen13',
  :adapter => 'mysql2',
  :database => 'snacks'
)

#
# Class definitions
#
class User < ActiveRecord::Base

  def to_s
    name
  end

end

# TODO: Your class definitions should be placed here.


#
# Core functions.
#
def list_users
  users = User.all
  users.each do |user|
    puts user
  end
end

# TODO: Your other menu-driven functions should be placed here.

def main_menu
  puts "\nMain Menu."
  puts "A. List Buildings"
  puts "B. List Machines"
  puts "C. List Snacks"
  puts "D. List Users"
  puts "E. Find a Snack"
  puts "F. Add a New Snack"
  puts "Q. Quit"
end

def execute_command(command)
  case command
  when "A"
    puts "\nListing Buildings"
    # TODO list_buildings
  when "B"
    puts "\nListing Machines"
    # TODO list_machines
  when "C"
    puts "\nListing Snacks"
    # TDOO list_snacks
  when "D"
    puts "\nListing Users"
    list_users
  when "E"
    puts "\nFind a Snack"
    # TDOO find_snack
  when "F"
    puts "\nAdding a new Snack"
    # TDOO add_snack
  when "Q"
    puts "Quitting... buh-bye."
  else
    puts "Sorry, I don't know how to do that. Too bad so sad."
  end
end

command = nil
puts "Snack Attack. Whee!"
while (command != 'Q')
  main_menu
  execute_command(command = gets.chomp!)
end