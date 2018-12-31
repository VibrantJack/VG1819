#pragma once
#include "kitten\K_Component.h"
#include "puppy\lights\P_DirectionalLight.h"

namespace kitten
{
	class K_DirectionalLight : public K_Component, public TransformPositionListener
	{
	private:
		puppy::P_DirectionalLight m_puppyLight;
		bool m_usingCallbacks;

		virtual void start() override;
		virtual bool hasUpdate() const override { return true; }
		virtual void update() override;

		virtual void onPosChanged(const glm::vec3& p_newPos) override;
	public:
		K_DirectionalLight(const glm::vec3& p_ambientColor, const glm::vec3& p_directionalColor, bool p_useTransformCallbacks = false);
		~K_DirectionalLight();

		void setAmbientColor(const glm::vec3& p_color);
		const glm::vec3& getAmbientColor() const;

		void setDirectionalColor(const glm::vec3& p_color);
		const glm::vec3& getDirectionalColor() const;
	};
}
