#pragma once

#include "TestRenderer.h"

#include <Texture.h>
#include <D3DManager.h>


using namespace DirectX;
using namespace UniDx;


VertexPT vertex[4] = {
    {{-0.5,-0.5,0},{0,1}},
    {{-0.5,0.5,0},{0,0}},
    {{0.5,-0.5,0},{1,1}},
    {{0.5,0.5,0},{1,0}},
};


void TestRenderer::OnEnable()
{
    Renderer::OnEnable();

    // �}�e���A����ǉ�
    materials.push_back(std::make_unique<Material>());

    // �}�e���A�����V�F�[�_�[��ǂݍ���ŏ�����
    materials.back()->initialize<VertexPT>(L"../UniDx/Albedo.hlsl");

    // �e�N�X�`����ǂݍ���Ń}�e���A���ɒǉ�
    std::unique_ptr<Texture> t = std::make_unique<Texture>();
    t->load(L"Resource/floor.png");
    materials.back()->addTexture(std::move(t));

    // �쐬����o�b�t�@�̎d�l�����߂�
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
    vbDesc.ByteWidth = sizeof(vertex);				// �쐬����o�b�t�@�̃o�C�g�T�C�Y
    vbDesc.MiscFlags = 0;							// ���̑��̃t���O
    vbDesc.StructureByteStride = 0;					// �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
    vbDesc.Usage = D3D11_USAGE_DEFAULT;				// �쐬����o�b�t�@�̎g�p�@
    vbDesc.CPUAccessFlags = 0;

    // ��̎d�l��n���Ē��_�o�b�t�@������Ă��炤
    D3D11_SUBRESOURCE_DATA initData = { vertex, sizeof(vertex), 0 };	// �������ރf�[�^

    // ���_�o�b�t�@�̍쐬
    D3DManager::instance->GetDevice()->CreateBuffer(&vbDesc, &initData, &vb);
}


void TestRenderer::Render(const UniDx::Camera& camera)
{
    // ���݂�Transform�ƃJ�����̏����V�F�[�_�[��ConstantBuffer�ɓ]��
    Renderer::UpdatePositionCameraCBuffer(camera);

    // �`�揈��
    // �O�p�`�̕`��
    {
        //++++++++++++++++++++ ��������`�悵�Ă����܂� ++++++++++++++++++++

        // ���_�o�b�t�@��`��Ŏg����悤�ɃZ�b�g����
        UINT stride = sizeof(VertexPT);
        UINT offset = 0;
        D3DManager::instance->GetContext()->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);

        // �v���~�e�B�u�E�g�|���W�[���Z�b�g
        D3DManager::instance->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

        //-----------------------------
        // �V�F�[�_�[���Z�b�g
        //-----------------------------
        SetShaderForRender();

        //-----------------------------
        // �`����s
        //-----------------------------
        // �f�o�C�X�R���e�L�X�g�A��L�̃Z�b�g�������e�ŕ`�悵�Ă��������A�Ƃ��肢����
        D3DManager::instance->GetContext()->Draw(4, 0);
    }
}
