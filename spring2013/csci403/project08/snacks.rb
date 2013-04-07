#!/usr/bin/env ruby

require 'rubygems'
require 'active_record'
require 'logger'

#
# Configuration
#
#ActiveRecord::Base.logger = Logger.new(STDOUT) # Comment this line to turn off log output

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
class Building < ActiveRecord::Base
  has_many :machines
  def to_s
    name
  end
end

class Machine < ActiveRecord::Base
  belongs_to :building #foreign key - building_id
  has_and_belongs_to_many :snacks
  def to_s
    serial_number
  end
end

class Snack < ActiveRecord::Base
  has_and_belongs_to_many :machines
  def to_s
    name
  end
end


#
# Core functions.
#

#A - List Buildings
def list_buildings
  buildings = Building.all
  buildings.each do |building|
    puts "#{building} (#{building.machines.count} machines)"
  end
end

#B - List Machines
def list_machines
  machines = Machine.all 
  machines.each do |machine|
    puts "#{machine.serial_number}, #{machine.description}"
  end
end

#C - List Snacks
def list_snacks
  snacks = Snack.all 
  snacks.each do |snack|
    puts "#{snack}"
    snack.machines.each do |machine|
      puts "- #{machine.serial_number} in #{machine.building.name} Building"
    end
  end
end

#D - List Users
def list_users
  users = User.all
  users.each do |user|
    puts "#{user}"
  end
end

#E - Find a Snack
def find_snack
  puts "Snack? "
end

#F - Add a Snack
def add_snack
  puts "yo"
end

#G - Add a User
def add_user
  puts "hello"
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
  puts "G. Create New User"
  puts "Q. Quit"
end

def execute_command(command)
  case command
  when "A", "a"
    puts "\nListing Buildings:"
    list_buildings
  when "B", "b"
    puts "\nListing Machines:"
    list_machines
  when "C", "c"
    puts "\nListing Snacks:"
    list_snacks
  when "D", "d"
    puts "\nListing Users:"
    list_users
  when "E", "e"
    puts "\nFind a Snack:"
    find_snack
  when "F", "f"
    puts "\nAdding a new Snack:"
    add_snack
  when "G", "g"
    puts "\nCreating a new User:"
    add_user
  when "Q"
    puts "Exiting..."
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