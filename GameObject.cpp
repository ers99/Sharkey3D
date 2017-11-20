#include "GameObject.h"



GameObject::GameObject(float vertices[], int size, ShaderLoader &shader, GLuint &_tex, glm::vec3 position) : mPosition(position), mVelocity(0,0,0), mScale(1,1,1), mShader(shader), GLTexture(_tex), onGround(false), isUpdating(true)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER ,VBO);

	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	//Position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Texture data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	mAcceleration = glm::vec3(0.0f, -9.8f, 0.0f);
}

GameObject::~GameObject()
{
	/*glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);*/

}

void GameObject::Draw()
{
	glBindTexture(GL_TEXTURE_2D, GLTexture);
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, mPosition);
	model = glm::scale(model, mScale);
	mShader.setMatrix4fv("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void GameObject::update(float deltaTime)
{
	if (isUpdating)
	{
		mPosition += mVelocity * deltaTime;
		mVelocity += mAcceleration * deltaTime;
		if (mPosition.y < 0.75f)
		{
			mPosition.y = 0.75f;
			mVelocity.y = 0;
			onGround = true;
		}

		if (onGround)
		{
			if (abs(mVelocity.x) < 0.1f && abs(mVelocity.z) < 0.1f)
			{
				mVelocity = glm::vec3();
				isUpdating = false;
			}
			frictionVec = glm::normalize(glm::vec3(mVelocity.x, 0, mVelocity.z));
			mVelocity -= frictionVec * deltaTime * 5.0f;
			mAcceleration.y = 0;
		}
	}

}

GameObject & GameObject::scale(glm::vec3 _scale)
{
	mScale = _scale;
	return *this;
}
