#include "Map.h"


Map::Map() {
	camera.x = 256;
	camera.y = 256;

	Simplex terrain;
	terrain.init();

	double scale = 0.07;

	// init map
	for (int x=0; x < 512; x++) {
		for (int y=0; y < 512; y++) {
			map[x][y] = Tile(GROUND);
			// noise grass
			double noise = (terrain.noise(x*scale, y*scale)+1)/2;
			map[x][y].color = fcolor(0, noise, 0, 1);
			if (noise < 0.23) map[x][y].type = WATER;
			if (noise < 0.1)  map[x][y].type = DEEPWATER;
			if (noise > 0.6)  map[x][y].type = TREE;
		}
	}

	for (int i=260; i<271; i++) for (int j=260; j<271; j++) map[i][j].type = FLOOR;
	for (int i=260; i<271; i++) map[i][260].type = WALL;
	for (int i=260; i<271; i++) map[i][270].type = WALL;
	for (int i=260; i<271; i++) map[260][i].type = WALL;
	for (int i=260; i<271; i++) map[270][i].type = WALL;
	for (int i=250; i<255; i++) map[250][i].type = WALL;
	for (int i=250; i<255; i++) map[i][250].type = WALL;

	map[265][260].type = GROUND;

	lights.emplace_back(Light({1.f, 0.7f, 0.7f, 1.f}, {256, 256}));
}


void Map::update(float dt) {
	timer += dt;
}

void Map::render(
	sf::RenderWindow* window,
	sf::Vector2i player,
	sf::Text& text,
	std::vector<std::string>& output,
	bool matrix)
{
	// update camera based on player position
	camera.x = player.x;
	camera.y = player.y;
	if (camera.x < 32) camera.x = 32;
	if (camera.y < 29) camera.y = 29;
	if (camera.x > 512-32) camera.x = 512-32;
	if (camera.y > 512-29) camera.y = 512-29;

	/// shitty fov check
	// reset visibility
	for (int x=0;x<512;x++) for (int y=0;y<512;y++) map[x][y].visible=false;
	// check for line of site
	for (int i = 0; i < 360; i++) {
		float x = cos((float)i*0.01745f);
		float y = sin((float)i*0.01745f);
		float ox=player.x+0.5f, oy=player.y+0.5f;
		for (int j = 0; j < 12; j++)
		{
			if (ox < 0) ox = 0;
			if (oy < 0) oy = 0;
			if (ox > 511) ox = 511;
			if (oy > 511) oy = 511;
			auto item = itemAtPos((int)ox, (int)oy);
			map[(int)ox][(int)oy].visible = true;
			map[(int)ox][(int)oy].discovered = true;
			if (map[(int)ox][(int)oy].type == WALL)
				break;
			if ((item != nullptr && item->getChar() == '+')) {
					ox += x*0.1;
					oy += y*0.1;
					continue;
			}
			int tiletype = map[(int)ox][(int)oy].type;
			if (tiletype==DEEPWATER || tiletype==TREE) {
				ox += x*0.5;
				oy += y*0.5;
				continue;
			}
			ox += x;
			oy += y;
		}
	}

	/// WORLD
	for (int x=0; x < 64; x++) {
		for (int y=0; y < 58; y++) {

			int mx=camera.x-32+x, my=camera.y-29+y;

			fcolor dif(1, 1, 1, 1);
			//for (auto light : lights)
			//	if (light.position.x > camera.x-16 && light.position.x < camera.x+16 && light.position.y > camera.y-16 && light.position.y < camera.y+16)
			//		if (pow(mx - light.position.x, 2) + pow(my - light.position.y, 2) < pow(light.radius, 2))
			//			dif = fcolor(light.color);

			TILE tile = map[mx][my].type;
			text.setPosition(15+x*12, 5+y*12);
			fcolor tcolor = map[mx][my].color;
			switch (tile)
			{
			case GROUND:
				//text.setFillColor(sf::Color(100*dif.r, 100*dif.g, 100*dif.b, 255*dif.a));
				text.setFillColor(sf::Color(50+tcolor.r*205, 50+tcolor.g*205, 50+tcolor.b*205, tcolor.a*255));
				text.setString(".");
				break;
			case WALL:
				text.setFillColor(sf::Color(200*dif.r, 200*dif.g, 200*dif.b, 255*dif.a));
				text.setString("#");
				break;
			case DOOR:
				text.setFillColor(sf::Color(200, 200, 200, 255));
				text.setString("-");
				break;
			case LOCKEDDOOR:
				text.setFillColor(sf::Color(200, 200, 200, 255));
				text.setString("+");
			case WATER:
				text.setFillColor({125, 125, 255, 255});
				text.setPosition(15+x*12, floor(5+y*12+cos(1.2*(my+mx+timer))*3));
				text.setString("~");
				break;
			case DEEPWATER:
				text.setFillColor({50, 50, 150, 255});
				text.setPosition(15+x*12, floor(5+y*12+cos(1*(my+mx+timer))*2));
				text.setString("~");
				break;
			case FLOOR:
				text.setFillColor({110, 110, 110, 255});
				text.setString("#");
				break;
			case TREE:
				text.setFillColor(sf::Color(90, 125, 90, tcolor.a*255));
				text.setString('T');
				break;
			default:
				text.setFillColor(sf::Color(200, 200, 200, 255));
				text.setString("H");
				break;
			}
			// I'm so fucking sorry..
			if (matrix && (float)rand()/RAND_MAX > 0.7f && tile == GROUND) {
				text.setString((table[rand()%strlen(table)-1]));
			}
			for (auto& cap : EntityHandler::getInstance()->getEntities()) {
				if (cap->x == mx && cap->y == my) {
					text.setFillColor({200, 200, 200, 255});
					text.setString(cap->h->getChar());
				}
			}
			if (mx == player.x && my == player.y) {
				text.setFillColor(sf::Color(155, 200, 155, 255));
				text.setString("@");
			}
			if (!map[mx][my].visible) {
				text.setString(".");
				text.setFillColor({10, 10, 10, 0});
			}
			if (!map[mx][my].visible && map[mx][my].discovered) {
				text.setString(".");
				text.setFillColor({0, 0, 0, 255});
			}

			window->draw(text);
		}
	}
}

void Map::renderPreview(sf::RenderWindow* window, sf::Text& text)
{
	static sf::RectangleShape shape {sf::Vector2f{1,1}};
	for (int x = 0; x < 512; x++)
	{
		for (int y = 0; y < 512; y++)
		{
			shape.setPosition(sf::Vector2f{x, y});
			TILE type = map[x][y].type;

			switch (type)
			{
			case GROUND:
				shape.setFillColor(sf::Color{100, 155, 100});
				break;
			case WATER:
				shape.setFillColor(sf::Color{100, 100, 155});
				break;
			case DEEPWATER:
				shape.setFillColor(sf::Color{100, 100, 255});
				break;
			case WALL:
				shape.setFillColor(sf::Color{200, 200, 200});
				break;
			case TREE:
				shape.setFillColor(sf::Color{20, 100, 20});
				break;
			}

			window->draw(shape);
		}
	}
}

/*
void Map::save(SQLite::Database& db)
{
	try {
		db.exec("CREATE TABLE IF NOT EXISTS map (id INTEGER PRIMARY KEY, x INTEGER, y INTEGER, type INTEGER)");
	} catch (SQLite::Exception& e) {
		std::cout << e.what() << std::endl;
	}
	SQLite::Transaction cmd(db);
	int k = 0;
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			std::stringstream ss;
			ss <<"INSERT OR REPLACE INTO map VALUES("<<k<<","<<i<<","<<j<<","<<map[i][j].type<<")";
			db.exec(ss.str());
			k++;
		}
	}
	cmd.commit();
}
*/

Item* Map::itemAtPos(int x, int y) {
	for (auto& cap : EntityHandler::getInstance()->getEntities()) {
		if (cap->x == x && cap->y == y)
			return cap->h;
	}
	return nullptr;
}
