/*********************************************************************
 * @file	transform.h
 * @author	SleepingDog0529
 * @date	2021/07/06 13:43
*********************************************************************/
#pragma once
#include "component.h"
#include <DirectXMath.h>

namespace wx2 {

	class Transform : public AbstractComponent
	{
		WX3_DECLARE_COMPONENTS_IMPL(Transform);

	public:
		Transform() = default;
		virtual ~Transform() = default;

		void Update() override;
		void Draw() override;

		const DirectX::XMMATRIX& GetWorldMatrix();

		const DirectX::XMVECTOR& GetPosition();
		const DirectX::XMVECTOR& GetRotation();
		const DirectX::XMVECTOR& GetScale();

		const DirectX::XMVECTOR& GetLeft();
		const DirectX::XMVECTOR& GetUp();
		const DirectX::XMVECTOR& GetForward();

		void SetWorldMatrix(const DirectX::XMMATRIX& world_matrix);

		void SetPosition(const DirectX::XMVECTOR& position);
		void SetRotation(const DirectX::XMVECTOR& rotation);
		void SetScale(const DirectX::XMVECTOR& scale);

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

	private:
		void UpdateWorldMatrix();
		void UpdateDirectionVectors();

		DirectX::XMMATRIX world_matrix_;

		DirectX::XMVECTOR position_;
		DirectX::XMVECTOR rotation_;
		DirectX::XMVECTOR scale_;

		DirectX::XMVECTOR left_    = kDefaultLeft_;
		DirectX::XMVECTOR up_      = kDefaultUp_;
		DirectX::XMVECTOR forward_ = kDefaultForward_;

		static constexpr DirectX::XMVECTORF32 kDefaultLeft_    = { 1.0f, 0.0f, 0.0f, 0.0f };
		static constexpr DirectX::XMVECTORF32 kDefaultUp_      = { 0.0f, 1.0f, 0.0f, 0.0f };
		static constexpr DirectX::XMVECTORF32 kDefaultForward_ = { 0.0f, 0.0f, 1.0f, 0.0f };
	};

}