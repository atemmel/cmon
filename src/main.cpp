#include "bitmaptext.hpp"
#include "path.hpp"
#include "healthbar.hpp"
#include "animatedsprite.hpp"
#include "resourcemanager.hpp"

struct ElementDerefLess
{
	bool operator()(const std::shared_ptr<Element> & lhs,
		const std::shared_ptr<Element> & rhs) const
	{
		return lhs->zIndex < rhs->zIndex;
	} 
};

const static sf::VideoMode DefaultMode(1024, 768);

static bool fullscreen = 0;

int main()
{
	ResourceManager manager;
	std::vector<std::shared_ptr<Element>> elements;

	const std::string p1Path = Path::Textures::BattlerBack + "001b.png",
		p2Path = Path::Textures::BattlerFront + "094.png";

	manager.loadFromFile<Texture>(Path::Textures::BattleUiPlayerBox);
	manager.loadFromFile<Texture>(Path::Textures::BattleUiEnemyBox);
	manager.loadFromFile<Texture>(Path::Textures::Background);
	manager.loadFromFile<Texture>(Path::Textures::MessageBox);
	manager.loadFromFile<Texture>(p1Path);
	manager.loadFromFile<Texture>(p2Path);
	manager.loadFromFile<Texture>(Path::Fonts::Message);
	manager.loadFromFile<BitmapFont>(Path::Fonts::MessageData);

	auto bmt = manager.access<Texture>(Path::Fonts::Message);
	auto bmf = manager.access<BitmapFont>(Path::Fonts::MessageData);

	std::shared_ptr<Sprite> p1Frame = std::make_shared<Sprite>(*manager.access<Texture>(Path::Textures::BattleUiPlayerBox));
	std::shared_ptr<Sprite> p2Frame = std::make_shared<Sprite>(*manager.access<Texture>(Path::Textures::BattleUiEnemyBox));
	std::shared_ptr<Sprite> background = std::make_shared<Sprite>(*manager.access<Texture>(Path::Textures::Background));
	std::shared_ptr<Sprite> messageBox = std::make_shared<Sprite>(*manager.access<Texture>(Path::Textures::MessageBox));

	std::shared_ptr<BitmapText> p1Name = std::make_shared<BitmapText>(*bmt, *bmf);
	std::shared_ptr<BitmapText> p2Name = std::make_shared<BitmapText>(*bmt, *bmf);
	std::shared_ptr<BitmapText> upperText = std::make_shared<BitmapText>(*bmt, *bmf);
	std::shared_ptr<BitmapText> lowerText = std::make_shared<BitmapText>(*bmt, *bmf);

	std::shared_ptr<HealthBar> p1Bar = std::make_shared<HealthBar>(sf::Vector2f(154.f, 6.7f));
	std::shared_ptr<HealthBar> p2Bar = std::make_shared<HealthBar>(sf::Vector2f(153.5f, 7.f));
	std::shared_ptr<AnimatedSprite> p1Sprite = std::make_shared<AnimatedSprite>(*manager.access<Texture>(p1Path));
	std::shared_ptr<AnimatedSprite> p2Sprite = std::make_shared<AnimatedSprite>(*manager.access<Texture>(p2Path));

	elements.push_back(p1Frame);
	elements.push_back(p2Frame);
	elements.push_back(background);
	elements.push_back(messageBox);

	elements.push_back(p1Name);
	elements.push_back(p2Name);
	elements.push_back(upperText);
	elements.push_back(lowerText);

	elements.push_back(p1Bar);
	elements.push_back(p2Bar);
	elements.push_back(p1Sprite);
	elements.push_back(p2Sprite);

	background->zIndex = 0;
	p2Sprite->zIndex = p1Sprite->zIndex = 1;
	p1Frame->zIndex = p2Frame->zIndex = messageBox->zIndex = 2;
	p1Bar->zIndex = p2Bar->zIndex = 3;
	p1Name->zIndex = p2Name->zIndex = upperText->zIndex = lowerText->zIndex = 4;

	p1Frame->setScale(1.6f);
	p2Frame->setScale(1.6f);
	p1Frame->setPosition(640.f, 500.f);
	p2Frame->setPosition(0.f, 40.f);
	messageBox->setPosition(0.f, 634.f);
	messageBox->setScale(1.6f);

	p1Name->setScale(1.6f);
	p1Name->setString("BULBASAUR");
	p1Name->setPosition(sf::Vector2f(690.f, 532.f));
	p1Bar->setPosition(sf::Vector2f(819.f, 538.f));
	
	p2Name->setScale(1.6f);
	p2Name->setString("GENGAR");
	p2Name->setPosition(sf::Vector2f(60.f, 72.f));
	p2Bar->setPosition(sf::Vector2f(141.f, 78.f));

	upperText->setScale(1.6f);
	upperText->setString("This is the upper text!");
	upperText->setPosition(sf::Vector2f(10.f, 688.f));

	lowerText->setScale(1.6f);
	lowerText->setString("Is this the lower text?");
	lowerText->setPosition(sf::Vector2f(10.f, 738.f));
	
	p1Sprite->setScale(3.f);
	p1Sprite->setPosition(sf::Vector2f(100.f, 300.f));
	p2Sprite->setScale(3.f);
	p2Sprite->setPosition(sf::Vector2f(300.f, 100.f));

	sf::RenderWindow window(DefaultMode, "");
	window.setFramerateLimit(60u);

	auto backgroundPtr = manager.access<Texture>(Path::Textures::Background);
	sf::Vector2f size = static_cast<sf::Vector2f>(backgroundPtr->getSize());
	sf::View view = window.getView();
	view.setSize(size);
	view.setCenter(size / 2.f);

	float health = 1.f;

	std::sort(elements.begin(), elements.end(), ElementDerefLess());

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed) window.close();
			else if(event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Key::F8)
				window.close();

			else if(event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Enter
				&& event.key.alt)
			{
				uint32_t style = 0;
				sf::VideoMode mode;

				if(fullscreen)
				{
					style = sf::Style::Default;
					mode = DefaultMode;
				}
				else
				{
					style = sf::Style::None;
					mode = sf::VideoMode::getDesktopMode();
				}

				window.close();
				window.create(mode, "", style);
				window.setFramerateLimit(60);
		
				fullscreen ^= 1;	//Toggle

				if(fullscreen) window.setMouseCursorVisible(false);
			}

			else if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Key::H)
				{
					health -= 0.01f;
					p1Bar->setHealth(health);
				}
			}
		}
		
		p1Sprite->next();
		p2Sprite->next();

		window.setView(view);
		window.clear();

		if(!std::is_sorted(elements.begin(), elements.end(), ElementDerefLess()))
		{
			std::sort(elements.begin(), elements.end(), ElementDerefLess());
		}

		for(auto & element : elements)
		{
			window.draw(*element);
		}

		window.display();
	}
	return 0;
}
