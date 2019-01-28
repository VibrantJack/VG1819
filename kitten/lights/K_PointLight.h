#pragma once
#include "kitten\K_Component.h"
#include "puppy\lights\P_PointLight.h"

namespace kitten
{
	class K_PointLight : public K_Component, public TransformPositionListener
	{
	private:
		puppy::P_PointLight m_puppyLight;
		bool m_usingCallbacks;

		virtual void start() override;
		virtual bool hasUpdate() const override { return true; }
		virtual void update() override;

		virtual void onPosChanged(const glm::vec3& p_newPos) override;
	public:
		K_PointLight(const glm::vec3& p_ambientColor, const glm::vec3& p_pointColor, const glm::vec3& p_attenuation, const float& p_range, bool p_useTransformCallbacks = false);
		~K_PointLight();

		void setAmbientColor(const glm::vec3& p_color);
		const glm::vec4& getAmbientColor() const;

		void setPointColor(const glm::vec3& p_color);
		const glm::vec4& getPointColor() const;

		void setAttenuation(const glm::vec3& p_atten);
		const glm::vec3& getAttenuation() const;

		void setRange(const float& p_range);
		const float& getRange() const;
	};
}
