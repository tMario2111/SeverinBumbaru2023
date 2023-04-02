#include "ShadowCaster.hpp"

namespace mke
{
	ShadowCaster::ShadowCaster(sf::RenderWindow& win) :
		win{ win },
		vision_triangle_fan{ sf::PrimitiveType::TriangleFan }
	{
		render_texture.create(win.getSize().x, win.getSize().y);

		shader_data =
		R"(
		uniform vec2 u_resolution;
		uniform sampler2D u_texture;
		void main()
		{
			vec2 st = gl_FragCoord.xy / u_resolution.xy;
			vec4 texture = texture2D(u_texture, st);
			gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0 - texture.r);
		}
		)";
		shader.loadFromMemory(shader_data, sf::Shader::Fragment);	
	}

	void ShadowCaster::setRadius(float radius)
	{
		this->radius = radius;
	}

	float ShadowCaster::getRadius()
	{
		return radius;
	}

	bool ShadowCaster::getLineIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, sf::Vector2f& p5)
	{
		auto dx12 = p2.x - p1.x;
		auto dy12 = p2.y - p1.y;
		auto dx34 = p4.x - p3.x;
		auto dy34 = p4.y - p3.y;
		auto denominator = (dy12 * dx34 - dx12 * dy34);
		auto t1 = ((p1.x - p3.x) * dy34 + (p3.y - p1.y) * dx34) / denominator;
		if (isinf(t1))
		{
			p5 = sf::Vector2f{ NAN, NAN };
			return false;
		}
		auto t2 = ((p3.x - p1.x) * dy12 + (p1.y - p3.y) * dx12) / -denominator;
		p5 = sf::Vector2f{ p1.x + dx12 * t1, p1.y + dy12 * t1 };
		return ((t1 >= 0) && (t1 <= 1) && (t2 >= 0) && (t2 <= 1));
	}

	void ShadowCaster::calculateVisibility(sf::Vector2f reference_point)
	{
		std::vector<sf::Vector2f> corners{};
		for (const auto& i : edges)
		{
			corners.push_back(i.first);
			corners.push_back(i.second);
		}

		std::sort(corners.begin(), corners.end(), [](const sf::Vector2f& A, const sf::Vector2f& B)
		{
			if (A.y > B.y)
				return true;
			if (A.y == B.y && A.x > B.x)
				return true;
			return false;
		});
		corners.resize(std::distance(corners.begin(), std::unique(corners.begin(), corners.end())));

		rays.clear();
		const auto angle_diff = 0.00001f;
		for (const auto& i : corners)
		{
			Ray ray{};
			const auto angle = atan2f(i.y - reference_point.y, i.x - reference_point.x);

			ray.position.x = reference_point.x + radius * cosf(angle);
			ray.position.y = reference_point.y + radius * sinf(angle);
			ray.angle = angle;
			rays.push_back(ray);

			ray.position.x = reference_point.x + radius * cosf(angle + angle_diff);
			ray.position.y = reference_point.y + radius * sinf(angle + angle_diff);
			ray.angle = angle + angle_diff;
			rays.push_back(ray);

			ray.position.x = reference_point.x + radius * cosf(angle - angle_diff);
			ray.position.y = reference_point.y + radius * sinf(angle - angle_diff);
			ray.angle = angle - angle_diff;
			rays.push_back(ray);
		}

		for (auto& i : rays)
		{
			auto min = INFINITY;
			for (auto& j : edges)
			{
				sf::Vector2f intersection{};
				if (getLineIntersection(reference_point, i.position, j.first, j.second, intersection))
				{
					const auto dist = mke::distance(intersection, reference_point);
					if (dist < min)
					{
						i.position = intersection;
						min = dist;
					}
				}
			}
		}

		std::sort(rays.begin(), rays.end(), [](const auto& a, const auto& b)
		{
			return a.angle > b.angle;
		});
	}

	void ShadowCaster::createTriangleFan(sf::Vector2f reference_point)
	{
		vision_triangle_fan.clear();

		sf::Vertex vert{};
		vert.color = sf::Color::Red;
		vert.position = reference_point;
		vision_triangle_fan.append(vert);

		for (const auto& i : rays)
		{
			vert.position = i.position;
			vision_triangle_fan.append(vert);
		}

		if (!rays.empty())
		{
			vert.position = rays[0].position;
			vision_triangle_fan.append(vert);
		}
	}

	void ShadowCaster::drawToRenderTexture()
	{
		render_texture.setView(win.getView());
		render_texture.clear();
		render_texture.draw(vision_triangle_fan);
		render_texture.display();

		shader.setUniform("u_resolution", static_cast<sf::Vector2f>(render_texture.getSize()));
		shader.setUniform("u_texture", render_texture.getTexture());
	}

	void ShadowCaster::update(sf::Vector2f reference_point)
	{
		calculateVisibility(reference_point);
		createTriangleFan(reference_point);
		drawToRenderTexture();
	}

	void ShadowCaster::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.shader = &shader;
		sf::RectangleShape rect(static_cast<sf::Vector2f>(win.getSize()));
		rect.setPosition(win.getView().getCenter().x - win.getView().getSize().x / 2,
			win.getView().getCenter().y - win.getView().getSize().y / 2);
		target.draw(rect, states);
	}
}