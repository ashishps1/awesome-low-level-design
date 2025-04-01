package musicstreamingservice

type MusicStreamingService struct {
	MusicLibrary     *MusicLibrary
	UserManager      *UserManager
	MusicRecommender *MusicRecommender
}

func NewMusicStreamingService() *MusicStreamingService {
	return &MusicStreamingService{
		MusicLibrary:     GetMusicLibrary(),
		UserManager:      GetUserManager(),
		MusicRecommender: GetMusicRecommender(),
	}
}
