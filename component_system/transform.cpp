#include "transform.h"

namespace wx2 {

	void Transform::Update()
	{

	}

	void Transform::Draw()
	{

	}

	const DirectX::XMMATRIX& Transform::GetWorldMatrix()
	{
		return world_matrix_;
	}

	const DirectX::XMVECTOR& Transform::GetPosition()
	{
		return position_;
	}

	const DirectX::XMVECTOR& Transform::GetRotation()
	{
		return rotation_;
	}

	const DirectX::XMVECTOR& Transform::GetScale()
	{
		return scale_;
	}

	const DirectX::XMVECTOR& Transform::GetLeft()
	{
		return left_;
	}

	const DirectX::XMVECTOR& Transform::GetUp()
	{
		return up_;
	}

	const DirectX::XMVECTOR& Transform::GetForward()
	{
		return forward_;
	}

	void Transform::SetWorldMatrix(const DirectX::XMMATRIX& world_matrix)
	{
		world_matrix_ = world_matrix;
		UpdateDirectionVectors();
	}

	void Transform::SetPosition(const DirectX::XMVECTOR& position)
	{
		position_ = position;
		UpdateWorldMatrix();
	}

	void Transform::SetRotation(const DirectX::XMVECTOR& rotation)
	{
		rotation_ = rotation;
		UpdateWorldMatrix();
		UpdateDirectionVectors();
	}

	void Transform::SetScale(const DirectX::XMVECTOR& scale)
	{
		scale_ = scale;
		UpdateWorldMatrix();
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		position_ = DirectX::XMVectorSet(x, y, z, 1.0f);
		UpdateWorldMatrix();
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		rotation_ = DirectX::XMVectorSet(x, y, z, 1.0f);
		UpdateWorldMatrix();
		UpdateDirectionVectors();
	}

	void Transform::SetScale(float x, float y, float z)
	{
		scale_ = DirectX::XMVectorSet(x, y, z, 1.0f);
		UpdateWorldMatrix();
	}

	void Transform::UpdateWorldMatrix()
	{
		using namespace DirectX;

		// ワールド行列を各ベクトルから求める
		world_matrix_ = XMMatrixIdentity();
		world_matrix_ *= XMMatrixScalingFromVector(scale_);
		world_matrix_ *= XMMatrixRotationRollPitchYawFromVector(rotation_);
		world_matrix_ *= XMMatrixTranslationFromVector(position_);
	}

	void Transform::UpdateDirectionVectors()
	{
		using namespace DirectX;

		// 回転行列
		XMMATRIX rotation_matrix =
			XMMatrixRotationRollPitchYaw(rotation_.m128_f32[0], rotation_.m128_f32[1], 0.0f);

		// 方向ベクトルに回転行列を適応
		left_ = XMVector3TransformCoord(kDefaultLeft_, rotation_matrix);
		up_ = XMVector3TransformCoord(kDefaultUp_, rotation_matrix);
		forward_ = XMVector3TransformCoord(kDefaultForward_, rotation_matrix);
	}

}