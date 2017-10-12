

#include "Game.h"

void Game::init()
{
    loadAreas();
    loadObstacles();
    loadItems();
    loadRooms();
    Player player(&rooms[0]);
    setPlayer(player);
    Monster monster(&rooms[2], "friendly monster");
    setMonsters(monster);
    UserInterface ui;
}

void Game::run()
{
    while(step()){
        ui.player_interact(player, monsters, rooms);
    }
}

void Game::loadAreas()
{
    areas.emplace_back("your bedroom");
    areas.emplace_back("the toilet of your apartment");
    areas.emplace_back("the hall of your apartment'");
    areas.emplace_back("an unknown room");
    areas.emplace_back("the long room you ever seen");
    areas.emplace_back("a room, with a lot of weirdly clean and shiny stares");
    areas.emplace_back("- Soo many doors - an other one leeds to a corridor.. again..");
}


void Game::loadObstacles() {
    obstacles.emplace_back("Locked Door",
                           "You do not remember the words to unlock it, you need your Wizzzard book to unlock it.");
}

void Game::loadItems() {
    items.emplace_back("wizzzard book", 10, "This is your not soo precious Wizzzard book", &obstacles[0]);
    items.emplace_back("toilet pump", 50, "One handed weepon");
    items.emplace_back("kitten", 99, "Wormhole Generator");
}

void Game::loadRooms() {
    rooms.emplace_back(&areas[0]);
    rooms.emplace_back(&areas[1]);
    rooms.emplace_back(&areas[2]);
    rooms.emplace_back(&areas[3]);
    rooms.emplace_back(&areas[4]);
    rooms.emplace_back(&areas[5]);
    rooms.emplace_back(&areas[6]);
    rooms.emplace_back(&areas[7]);

    // Call connections to every room. args: (room_number, North, East, South, West)
    connect_rooms(0, nullptr, nullptr, nullptr, &rooms[1]);
    connect_rooms(1, nullptr, &rooms[0], &rooms[2], nullptr);
    connect_rooms(2, &rooms[1], &rooms[3], nullptr, nullptr);
    connect_rooms(3, nullptr, &rooms[4], nullptr, &rooms[2]);
    connect_rooms(4, &rooms[5], nullptr, nullptr, &rooms[3]);
    connect_rooms(5, &rooms[6], nullptr, &rooms[4], nullptr);
    connect_rooms(6, &rooms[7], nullptr, &rooms[5], nullptr);
    connect_rooms(7, nullptr , nullptr, &rooms[6], nullptr);

    addItemsToRooms();

    obstacles_to_rooms(0, nullptr, nullptr, nullptr, nullptr);
    obstacles_to_rooms(1, nullptr, nullptr, nullptr, nullptr);
    obstacles_to_rooms(2, nullptr, nullptr, nullptr, nullptr);
    obstacles_to_rooms(3, nullptr, &obstacles[0], nullptr, nullptr);
    obstacles_to_rooms(4, nullptr, nullptr, nullptr, nullptr);
    obstacles_to_rooms(5, nullptr, nullptr, nullptr, nullptr);
    obstacles_to_rooms(6, nullptr, nullptr, nullptr, nullptr);
    obstacles_to_rooms(7, nullptr, nullptr, nullptr, nullptr);

}

void Game::connect_rooms(int room_number, Room* n_room, Room* e_room, Room* s_room, Room* w_room) {
    Room* rooms_direction[4];
    rooms_direction[direction::NORTH] = n_room;
    rooms_direction[direction::EAST] = e_room;
    rooms_direction[direction::SOUTH] = s_room;
    rooms_direction[direction::WEST] = w_room;

    Room** p_dir = &rooms_direction[0];

    rooms[room_number].set_connected_rooms(p_dir, sizeof(rooms_direction)/sizeof(rooms_direction[0]));
}

void Game::addItemsToRooms() {
    rooms[0].add_items(&items[0]);
    rooms[1].add_items(&items[1]);
    rooms[4].add_items(&items[2]);
}

void Game::obstacles_to_rooms(int room_number, Obstacle* to_north, Obstacle* to_east, Obstacle* to_south, Obstacle* to_west) {
    Obstacle* obs_direct[4];
    obs_direct[direction::NORTH] = to_north;
    obs_direct[direction::EAST] = to_east;
    obs_direct[direction::SOUTH] = to_south;
    obs_direct[direction::WEST] = to_west;

    Obstacle** p_dir = &obs_direct[0];
    rooms[room_number].set_obstacle(p_dir, sizeof(obs_direct)/sizeof(obs_direct[0]));
}


void Game::setPlayer(Player player) {
    this->player = player;
}

void Game::setMonsters(Monster monster) {
    monster.set_description(" It does not hurt you, but begs you to lead it to the wizzard lecture. Will you help?");
    monsters.push_back(monster);
}


bool Game::step()
{
    if(player.get_current_room() == &rooms.back()){
         cout << "Congratulations, you found your way to the classroom." << endl;
        return false;
    }
    return true;
}

